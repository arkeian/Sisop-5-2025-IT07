# Laporan Resmi Modul 5 Kelompok IT-07

## Kelompok

| Nama 				| NRP		|
|-------------------------------|---------------|
| Muhammad Rakha Hananditya R.	| 5027241015 	|
| Zaenal Mustofa		| 5027241018 	|
| Mochkamad Maulana Syafaat	| 5027241021 	|

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama `EorzeOS` untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

8. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

### Kernel

### Stdlib

### Shell

### Makefile

&emsp;Makefile merupakan sebuah file yang memiliki fungsi utama menuliskan daftar instruksi yang digunakan untuk menyederhanakan proses build dan compile program `EorzeOS` yang cenderung memiliki banyak command yang perlu dijalankan agar dapat dieksekusi. Makefile akan hanya menjalankan bagian instruksi yang diperlukan dan tidak akan menjalankan instruksi yang memiliki keluaran yang sudah ada dan tidak berubah dari proses build sebelumnya. Adapun tampilan file makefile yang digunakan pada program `EorzeOS` ini adalah sebagai berikut:

```make
ASM		= nasm
CC		= bcc
LINKER		= ld86
FLOPPY_IMG	= bin/floppy.img
INCLUDE_PATH	= include/
BOOTLOADER_SRC 	= src/bootloader.asm
BOOTLOADER_BIN 	= bin/bootloader.bin
KERNEL_ASM_SRC	= src/kernel.asm
KERNEL_C_SRC	= src/kernel.c
KERNEL_ASM_OBJ	= bin/kernel-asm.o
KERNEL_C_OBJ	= bin/kernel.o
KERNEL_BIN	= bin/kernel.bin
SHELL_C_SRC	= src/shell.c
SHELL_C_OBJ	= bin/shell.o
STDLIB_C_SRC	= src/std_lib.c
STDLIB_C_OBJ	= bin/std_lib.o
EMULATOR	= bochs
EMULATOR_SRC	= bochsrc.txt

prepare:
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880

bootloader:
	$(ASM) -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)
	dd if=$(BOOTLOADER_BIN) of=$(FLOPPY_IMG) bs=512 count=1 conv=notrunc

stdlib:
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(STDLIB_C_SRC) -o $(STDLIB_C_OBJ)

shell:
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(SHELL_C_SRC) -o $(SHELL_C_OBJ)

kernel:
	$(ASM) -f as86 $(KERNEL_ASM_SRC) -o $(KERNEL_ASM_OBJ)
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(KERNEL_C_SRC) -o $(KERNEL_C_OBJ)
	$(LINKER) -o $(KERNEL_BIN) -d $(KERNEL_C_OBJ) $(KERNEL_ASM_OBJ) $(SHELL_C_OBJ) $(STDLIB_C_OBJ)

link:
	dd if=$(KERNEL_BIN) of=$(FLOPPY_IMG) bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link
	$(EMULATOR) -f $(EMULATOR_SRC)
```

Di mana penjelasan setiap bagiannya:

#### Variabel Global

```make
ASM		= nasm
```
1. Variabel `ASM` menyimpan data terkait compiler yang pada kasus ini adalah `Netwide Assembler` atau disingkat `nasm` dan digunakan untuk proses mengubah kode bahasa assembly menjadi suatu file dengan format raw bianry yang dapat dieksekusi oleh processor.

```make
CC		= bcc
```
2. Variabel `CC` menyimpan data terkait compiler yang pada kasus ini adalah `Bruce's C Compiler` atau disingkat `bcc` dan digunakan untuk proses mengubah kode bahasa ANSI C (C89) menjadi suatu file objek.

```make
LINKER		= ld86
```
3. Variabel `LINKER` menyimpan data terkait program linker yang pada kasus ini adalah `ld86` yang merupakan suatu linker dari `bcc` untuk arsitektur 8086 dengan sistem 16-bit dan digunakan untuk menggabungkan file-file objek program ANSI C (C89) yang telah di-compile oleh `bcc` menjadi suatu file biner yang bisa dieksekusi oleh processor.

```make
FLOPPY_IMG	= bin/floppy.img
```
4. Variabel `FLOPPY_IMG` menyimpan data terkait alamat atau path dari file image floppy yang merupakan media virtual berukuran 1.44MB yanga akan digunakan oleh program emulator dari `Bochs` dan berisi file biner bootloader dan kernel yang telah di-compile sebelumnya menggunakan `nasm` dan `bcc` ke dalam urutan sektor yang sesuai yang pada kasus ini bootloader diletakkan pada sektor `0` (512 byte pertama) dan kernel yang diletakkan pada sektor-sektor selanjutnya, dimulai dari sektor `1`.

```make
INCLUDE_PATH	= include/
```
5. Variabel `INCLUDE_PATH` menyimpan data terkait alamat atau path dari direktori yang menyimpan file-file header yang digunakan oleh file program ANSI C (C89) agar dapat berjalan yang berisi pendefinisian fungsi atau prototipe fungsi dan pendefinisian konstanta.

```make
BOOTLOADER_SRC 	= src/bootloader.asm
```
6. Variabel `BOOTLOADER_SRC` menyimpan data terkait alamat atau path dari file sumber program assembly yang berhubungan dengan bootloader program `EorzeOS` dan nantinya akan di-compile menggunakan `nasm` menjadi suatu file biner.

```make
BOOTLOADER_BIN 	= bin/bootloader.bin
```
7. Variabel `BOOTLOADER_BIN` menyimpan data terkait alamat atau path dari file tujuan program assembly yang berhubungan dengan bootloader program `EorzeOS` dan merupakan hasil dari proses compile `BOOTLOADER_SRC` menggunakan `nasm` di mana `BOOTLOADER_BIN` merupakan suatu file biner.

```make
KERNEL_ASM_SRC	= src/kernel.asm
```
8. Variabel `KERNEL_ASM_SRC` menyimpan data terkait alamat atau path dari file sumber program assembly yang berhubungan dengan kernel program `EorzeOS` dan nantinya akan di-compile menggunakan `nasm` menjadi suatu file objek.

```make
KERNEL_C_SRC	= src/kernel.c
```
9. Variabel `KERNEL_C_SRC` menyimpan data terkait alamat atau path dari file sumber program ANSI C (C89) yang berhubungan dengan kernel program `EorzeOS` dan nantinya akan di-compile menggunakan `bcc` menjadi suatu file objek.

```make
KERNEL_ASM_OBJ	= bin/kernel-asm.o
```
10. Variabel `KERNEL_ASM_OBJ` menyimpan data terkait alamat atau path dari file tujuan program assembly yang berhubungan dengan kernel program `EorzeOS` dan merupakan hasil dari proses compile `KERNEL_ASM_SRC` menggunakan `nasm` di mana `KERNEL_ASM_OBJ` merupakan suatu file objek.

```make
KERNEL_C_OBJ	= bin/kernel.o
```
11. Variabel `KERNEL_C_OBJ` menyimpan data terkait alamat atau path dari file tujuan program ANSI C (C89) yang berhubungan dengan kernel program `EorzeOS` dan merupakan hasil dari proses compile `KERNEL_C_SRC` menggunakan `bcc` di mana `KERNEL_C_OBJ` merupakan suatu file objek.

```make
KERNEL_BIN	= bin/kernel.bin
```
12. Variabel `KERNEL_BIN` menyimpan data terkait alamat atau path dari file tujuan dari file objek yang berhubungan dengan kernel program `EorzeOS` dan merupakan hasil dari proses compile `KERNEL_C_OBJ`, `KERNEL_ASM_OBJ`, `SHELL_C_OBJ`, dan `STDLIB_C_OBJ` menggunakan `ld86` di mana `KERNEL_BIN` merupakan suatu file dengan format raw bianry yang dapat dieksekusi oleh processor.

```make
SHELL_C_SRC	= src/shell.c
```
13. Variabel `SHELL_C_SRC` menyimpan data terkait alamat atau path dari file sumber program ANSI C (C89) yang berhubungan dengan shell program `EorzeOS` dan nantinya akan di-compile menggunakan `bcc` menjadi suatu file objek.

```make
SHELL_C_OBJ	= bin/shell.o
```
14. Variabel `SHELL_C_OBJ` menyimpan data terkait alamat atau path dari file tujuan program ANSI C (C89) yang berhubungan dengan shell program `EorzeOS` dan merupakan hasil dari proses compile `SHELL_C_SRC` menggunakan `bcc` di mana `SHELL_C_OBJ` merupakan suatu file objek.

```make
STDLIB_C_SRC	= src/std_lib.c
```
15. Variabel `STDLIB_C_SRC` menyimpan data terkait alamat atau path dari file sumber program ANSI C (C89) yang berhubungan dengan stdlib program `EorzeOS` dan nantinya akan di-compile menggunakan `bcc` menjadi suatu file objek.

```make
STDLIB_C_OBJ	= bin/std_lib.o
```
16. Variabel `STDLIB_C_OBJ` menyimpan data terkait alamat atau path dari file tujuan program ANSI C (C89) yang berhubungan dengan stdlib program `EorzeOS` dan merupakan hasil dari proses compile `STDLIB_C_SRC` menggunakan `bcc` di mana `STDLIB_C_OBJ` merupakan suatu file objek.

```make
EMULATOR	= bochs
```
17. Variabel `EMULATOR` menyimpan data terkait program emulator yang pada kasus ini adalah `bochs` yang merupakan suatu emulator x86 open-source untuk melakukan proses virtualisasi program `EorzeOS`.

```make
EMULATOR_SRC	= bochsrc.txt
```
18. Variabel `EMULATOR_SRC` menyimpan data terkait konfigurasi dari program emulator yang pada kasus ini adalah `bochsrc.txt` dan digunakan agar emulator `bochs` dapat berjalan. File `bochsrc.txt` berisi berbagai pengaturan seperti lokasi file floppy image, jumlah RAM virtual, dan sebagainya.

#### Target dan Rule

### Kendala yang Dialami

### Revisi
