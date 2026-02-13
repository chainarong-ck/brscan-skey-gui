# การแพ็กโปรแกรมสำหรับแจกจ่าย (Packaging Guide)

เอกสารนี้รวบรวมวิธีการแพ็กโปรแกรม `brscan-skey-gui` เพื่อนำไปใช้งานบน Linux เครื่องอื่น

## 1. สร้าง Standalone Executable (แนะนำ)

วิธีนี้จะรวม Python และ Library ทั้งหมดไว้ในไฟล์เดียว (คล้าย .exe) สามารถก๊อปปี้ไปรันที่เครื่องอื่นได้เลย

**วิธีทำ:**

1. รัน script build:

   ```bash
   chmod +x build_standalone.sh
   ./build_standalone.sh
   ```

2. ไฟล์ที่ได้จะอยู่ที่ `dist/brscan-skey-gui`

**ข้อดี:** ง่าย, ไฟล์เดียวจบ
**ข้อเสีย:** ขนาดใหญ่ (~50MB+), อาจมีปัญหากับเครื่อง Linux ที่เก่ามากๆ (glibc version)

---

## 2. Linux Distribution Packages (.deb / .rpm)

หากต้องการทำไฟล์ติดตั้งมาตรฐานเช่น `.deb` หรือ `.rpm` แนะนำให้ใช้เครื่องมือ `fpm` (Effing Package Management)

### ตัวอย่างการสร้าง .deb (สำหรับ Debian/Ubuntu)

1. ติดตั้ง fpm (ต้องมี Ruby):

   ```bash
   sudo apt install ruby-dev build-essential
   sudo gem install fpm
   ```

2. สร้าง .deb จากโฟลเดอร์ source:

   ```bash
   fpm -s dir -t deb \
       -n brscan-skey-gui \
       -v 0.1.0 \
       -d "python3-pyside6.qtwidgets" \
       --prefix /usr/local/bin \
       src/main.py=brscan-skey-gui
   ```

---

## 3. AppImage

วิธีนี้ดีที่สุดสำหรับความเข้ากันได้ทุก Distro (Ubuntu, Fedora, Arch, etc.)

**วิธีทำ:**

1. ดาวน์โหลด `appimagetool` และ `linuxdeploy`
2. ใช้ script `linuxdeploy` เพื่อรวม Application

   ```bash
   wget https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/linuxdeploy-x86_64.AppImage
   chmod +x linuxdeploy-x86_64.AppImage
   
   ./linuxdeploy-x86_64.AppImage --appdir AppDir --output appimage \
       --desktop-file assets/brscan-skey-gui.desktop \
       --icon assets/icon.png \
       --executable dist/brscan-skey-gui
   ```

---

## สรุป

- **สำหรับแจกเพื่อน/ใช้งานเอง:** ใช้ **install.sh** (ง่ายที่สุด)
- **สำหรับแจกคนทั่วไป:** ใช้ **build_standalone.sh** (ไฟล์เดียว)
