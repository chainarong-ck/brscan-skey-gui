from dataclasses import dataclass
from pathlib import Path

@dataclass
class Config:
    resolution: str
    duplex: str
    size: str

class ConfigManager:
    CONFIG_DIR = Path.home() / ".brscan-skey"
    CONFIG_FILES = {
        "Scan to File": "scantofile.config",
        "Scan to Email": "scantoemail.config",
        "Scan to Image": "scantoimage.config",
        "Scan to OCR": "scantoocr.config"
    }
    DEFAULTS = Config(
        resolution="100",
        duplex="OFF",
        size="A4"
    )

    def __init__(self) -> None:
        """Initialize the configuration manager."""
        self._ensure_config_dir()

    def _ensure_config_dir(self) -> None:
        """Ensure the configuration directory exists."""
        self.CONFIG_DIR.mkdir(parents=True, exist_ok=True)

        for label, filename in self.CONFIG_FILES.items():
            path = self.CONFIG_DIR / filename
            if not path.exists():
                self._write_default_config(path)

    def _write_default_config(self, path: Path) -> None:
        """Write a default configuration file."""
        content = (
            "#[brscan-skey]\n\n"
            "# resolution=100,150,200,300,400,600,1200,2400,4800,9600\n"
            f"resolution={self.DEFAULTS.resolution}\n\n"
            "#duplex=OFF,ON\n"
            f"duplex={self.DEFAULTS.duplex}\n\n"
            "#size=MAX,A3,A4,A5,A6,Letter,Legal,${width}x${height} (mm)\n"
            f"size={self.DEFAULTS.size}\n"
        )
        path.write_text(content)

    def load_config(self, config_name: str) -> Config:
        """Loads configuration for a given config name (preserves comments)."""
        filename = self.CONFIG_FILES.get(config_name)
        if not filename:
            raise ValueError(f"Unknown config: {config_name}")

        path = self.CONFIG_DIR / filename
        config_data: dict[str, str] = {}

        try:
            for line in path.read_text().splitlines():
                line = line.strip()
                if not line or line.startswith("#"):
                    continue
                if "=" in line:
                    key, value = line.split("=", 1)
                    config_data[key.strip()] = value.strip()
        except FileNotFoundError:
            return self.DEFAULTS

        return Config(
            resolution=config_data.get("resolution", self.DEFAULTS.resolution),
            duplex=config_data.get("duplex", self.DEFAULTS.duplex),
            size=config_data.get("size", self.DEFAULTS.size)
        )

    def save_config(self, config_name: str, data: Config) -> None:
        """Saves configuration for a given config name."""
        filename = self.CONFIG_FILES.get(config_name)
        if not filename:
            raise ValueError(f"Unknown config: {config_name}")

        path = self.CONFIG_DIR / filename

        content = (
            "#[brscan-skey]\n\n"
            "# resolution=100,150,200,300,400,600,1200,2400,4800,9600\n"
            f"resolution={data.resolution}\n\n"
            "#duplex=OFF,ON\n"
            f"duplex={data.duplex}\n\n"
            "#size=MAX,A3,A4,A5,A6,Letter,Legal,${width}x${height} (mm)\n"
            f"size={data.size}\n"
        )

        path.write_text(content)
