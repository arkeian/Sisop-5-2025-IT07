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

7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

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

### • Kernel

<p align="justify">  
&emsp;&emsp;Pada program <code>EorzeOS</code>, kernel dibagi menjadi dua, yaitu <code>kernel.asm</code> yang merupakan program dengan basis bahasa assembly yang berinteraksi langsung secara low-level dengan perangkat keras komputer dan <code>kernel.c</code>, program dengan basis bahasa ANSI C (C89) yang memiliki fungsi sebagai program yang menjadi penghubung antara <code>kernel.asm</code> dengan program yang berinteraksi secara top-level dengan user, yang pada kasus <code>EorzeOS</code> merupakan program <code>shell.c</code>.  
</p>  

<p align="justify">  
&emsp;&emsp;Adapun pada penerapan sistem operasi kali ini, kita hanya diperintahkan untuk membuat dan mengimplementasikan program <code>kernel.c</code>, di mana untuk membuat <code>kernel.c</code> dibuatlah tiga function utama yaitu <code>printString()</code>, <code>readString()</code>, dan <code>clearScreen()</code> yang dalam implementasinya dibantu oleh tiga helper function di mana di antaranya terdiri atas <code>repositionXY()</code>, <code>scroll()</code>, dan <code>putc()</code>. Selain itu, terdapat beberapa function eksternal yang digunakan dengan implementasinya terletak pada program <code>kernel.asm</code> yang di antaranya terdiri atas <code>putInMemory()</code> dan <code>interrupt()</code>.  
</p>

Adapun tampilan `kernel.c` secara keseluruhan adalah sebagai berikut:

```c
#include "shell.h"
#include "kernel.h"

#define SEGMENT     0xB000
#define ADDRESS     0x8000
#define INT_VID     0x10
#define INT_KBD     0x16
#define TELETYPE    0X0E
#define KEYBOARD    0X00
#define MASK        0x00FF
#define VALID_ASCII 0X20
#define SCROLL      0x06
#define SCROLL_ONE  0x01
#define IGNORE      0x00
#define MAX_COLUMNS 80
#define MAX_ROWS    25
#define TAB_SIZE    4
#define BUFFER      128

static unsigned int _xPos = 0, _yPos = 0;
static unsigned int _xStart = 0, _yStart = 0;
static unsigned char _color = 0x0F;

enum KEYCODE {
  KEY_NEWLINE   = '\n',
  KEY_RETURN    = '\r',
  KEY_TAB       = 0x09,
  KEY_BACKSPACE = 0x08
};

void main() {
  clearScreen();
  shell();
}

void repositionXY(unsigned int x, unsigned int y) {
  _xPos = x;
  _yPos = y;
  _xStart = _xPos;
  _yStart = _yPos;
}

void scroll() {
  unsigned int ax, bx, cx, dx;

  ax = (SCROLL << 8) | SCROLL_ONE;
  bx = (_color << 8) | IGNORE;
  cx = (0 << 8) | 0;
  dx = ((MAX_ROWS - 1) << 8) | (MAX_COLUMNS - 1);

  interrupt(INT_VID, ax, bx, cx, dx);

  repositionXY(0, MAX_ROWS - 1);
}

void putc(unsigned char c) {
  unsigned int offset;

  if (c == 0) {
    return;
  }  
  else if (c == KEY_NEWLINE) {
    _xPos = _xStart;
    _yPos++;
    return;
  }

  if (_xPos >= MAX_COLUMNS) {
    _xPos = _xStart;
    _yPos++;
  }  

  if (_yPos >= MAX_ROWS) {
    scroll();
  }  

  offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;

  putInMemory(SEGMENT, offset, c);
  putInMemory(SEGMENT, offset + 1, _color);

  _xPos++;
}  


void printString(char *str)
{
  if (str == 0) {
    return;
  }  

  while(*str) {
    putc(*str);
    str++;
  }  
}  

void readString(char *buf) {
  unsigned char c;
  int bufPos = 0;
  unsigned int ax;
  unsigned int offset;
  int i;

  while (1) {
    ax = interrupt(INT_KBD, KEYBOARD, 0, 0, 0);
    c = (unsigned char)(ax & MASK);

    if (c == KEY_RETURN) {
      buf[bufPos] = '\0';
      putc(KEY_NEWLINE);
      break;
    }
    else if (c == KEY_TAB) {
      for (i = 0; i < TAB_SIZE; i++) {
        buf[bufPos] = ' ';
        bufPos++;
        putc(' ');
      }
    }  
    else if (c == KEY_BACKSPACE) {
      if (bufPos > 0) {
        bufPos--;

        if (_xPos > _xStart) {
          _xPos--;
        }  
        else if (_yPos > _yStart) {
          _yPos--;
          _xPos = MAX_COLUMNS - 1;
        }  

        offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;
  
        putInMemory(SEGMENT, offset, ' ');
        putInMemory(SEGMENT, offset + 1, _color);
      }  
    }  
    else {
      if (c >= VALID_ASCII && bufPos < BUFFER - 1) {
        buf[bufPos] = c;
        bufPos++;
        putc(c);
      }  
    }  
  }  
}  

void clearScreen() {
  unsigned int offset;
  int i, j;
  
  for (i = 0; i < MAX_ROWS; i++) {
    for (j = 0; j < MAX_COLUMNS; j++) {
      offset = ADDRESS + (i * MAX_COLUMNS + j) * 2;

      putInMemory(SEGMENT, offset, ' ');
      putInMemory(SEGMENT, offset + 1, _color);
    }  
  }  

  repositionXY(0, 0);
}
```

Di mana langkah implementasinya:

#### • Preprocessors

```c
#include "shell.h"
#include "kernel.h"
```
1. Menyertakan file-file header yang didefinisikan pada direktori `/include` di mana file header tersebut menyediakan elemen seperti deklarasi fungsi, makro, beserta definisi konstanta yang diperlukan dalam implementasi program `kernel.c`.

```c
#define SEGMENT     0xB000
```
2. Mendefinisikan makro `SEGMENT` yang merepresentasikan alamat segmen video memori yaitu `0XB000` pada arsitektur x86 di mana digunakan untuk tampilan VGA dengan mode teks.

```c
#define ADDRESS     0x8000
```
3. Mendefinisikan makro `ADDRESS` yang merepresentasikan alamat offset awal segmen video memori yaitu `0x8000` yang merupakan tempat karakter ASCII pertama pada layar akan ditampilkan.

```c
#define INT_VID     0x10
```
4. Mendefinisikan makro `INT_VID` yang merepresentasikan layanan interupsi video untuk BIOS dengan integer `0x10` atau `10h` di mana dalam penerapannya digunakan untuk menampilkan karakter ASCII pada layar menggunakan function `interrupt()`.

```c
#define INT_KBD     0x16
```
5. Mendefinisikan makro `INT_KBD` yang merepresentasikan layanan interupsi keyboard untuk BIOS dengan integer `0x16` atau `16h` di mana dalam penerapannya digunakan untuk melakukan proses interaksi dengan keyboard seperti membaca input menggunakan function `interrupt()`.

```c
#define TELETYPE    0X0E
```
6. Mendefinisikan makro `TELETYPE` dengan value `0x0E` yang merepresentasikan suatu subfungsi dari integer `0x10` atau `10h` di mana dalam penerapannya digunakan untuk menampilkan satu karakter ASCII ke layar dengan keluaran teletype (mesin ketik) dan setelahnya akan menggeser kursor ke kanan sebanyak satu karakter ASCII menggunakan function `interrupt()` dan melalui register `AH`.
  
	Namun, pada program `EorzeOS` subfungsi `TELETYPE` tidak digunakan karena pada proses penampilan karakter ASCII ke layar tidak menggunakan function `interrupt()`, melainkan menggunakan pendekatan manual dengan proses perhitungan offset pada layar ntuk menentukan letak di mana karakter ASCII akan diletakkan yang 		implementasinya diterapkan pada function `putc()` yang pada dasarnya dapat dilakukan dengan bantuan function `putInMemory()`.

```c
#define KEYBOARD    0X00
```
7. Mendefinisikan makro `KEYBOARD` dengan value `0x00` yang merepresentasikan suatu subfungsi dari integer `0x16` atau `16h` di mana dalam penerapannya digunakan untuk menunggu input dari keyboard dan akan membaca satu karakter ASCII menggunakan function `interrupt()` dan melalui register `AL`.

```c
#define MASK        0x00FF
```
8. Mendefinisikan makro `MASK` dengan value `0x00FF` yang merepresentasikan bitmask register `AX` yang merupakan register 16-bit yang terdiri atas dua register 8-bit yaitu register `AL` dan `AH` di mana dalam penerapannya digunakan untuk mengambil low byte dari register `AX` yang pada kasus ini merupakan register `AL` yang memuat karakter ASCII dan menghapus high byte dari register `AX` yang pada kasus ini merupakan register `AH`.

```c
#define VALID_ASCII 0X20
```
9. Mendefinisikan makro `VALID_ASCII` yang merepresentasikan suatu nilai heksadesimal di mana dalam penerapannya digunakan untuk mendefinisikan batas bawah untuk nilai  ASCII suatu karakter valid atau yang diperbolehkan untuk ditampilkan pada layar yang di mana pada program `EorzeOS`, batas bawahnya adalah `0x20` atau dalam format desimal adalah `32`.

```c
#define SCROLL      0x06
```
10. Mendefinisikan makro `SCROLL` dengan value `0x06` yang merepresentasikan suatu fungsi utama BIOS dari integer `0x10` atau `10h` di mana pada kasus program `EorzeOS` digunakan pada register `AH` yang merupakan high byte dari register `AX` yang digunakan untuk memungkinkan dilakukannya proses scrolling BIOS menggunakan function `scroll()` yang pada dasarnya dapat dilakukan dengan bantuan interupsi video untuk BIOS menggunakan function `interrupt()`.

```c
#define SCROLL_ONE  0x01
```
11. Mendefinisikan makro `SCROLL_ONE` dengan value `0x01` yang merepresentasikan suatu nilai parameter di mana pada kasus program `EorzeOS` digunakan pada register `AL` yang merupakan low byte dari register `AX` yang memuat banyaknya baris yang akan digeser ke atas saat melakukan proses scrolling BIOS menggunakan function `scroll()` yang pada dasarnya dapat dilakukan dengan bantuan interupsi video untuk BIOS menggunakan function `interrupt()`.

```c
#define IGNORE      0x00
```
12. Mendefinisikan makro `IGNORE` dengan value `0x00` yang merepresentasikan suatu nilai placeholder di mana dalam penerapannya digunakan untuk menyatakan nilai parameter yang tidak dibutuhkan dan diabaikan oleh BIOS yang pada kasus program `EorzeOS` digunakan pada register `BL` yang merupakan low byte dari register `BX` yang memuat nomor halaman dari layar yang pada kasus program `EorzeOS` dinyatakan dengan `0` saat melakukan proses scrolling BIOS menggunakan function `scroll()` di mana pada dasarnya dapat dilakukan dengan bantuan interupsi video untuk BIOS dengan integer `0x10` atau `10h` menggunakan function `interrupt()`.

```c
#define MAX_COLUMNS 80
#define MAX_ROWS    25
```
13. Mendefinisikan makro `MAX_COLUMNS` dan `MAX_ROWS` yang merepresentasikan suatu konstanta di mana dalam penerapannya digunakan untuk mendefinisikan batas maksimum ukuran layar yang di mana pada kasus program `EorzeOS`, ukuran yang ditentukan adalah ukuran standar VGA dengan mode teks yaitu `80` kolom dengan `25` baris.

```c
#define TAB_SIZE    4
```
14. Mendefinisikan makro `TAB_SIZE` yang merepresentasikan suatu konstanta di mana dalam penerapannya digunakan untuk mendefinisikan banyaknya spasi yang akan ditampilkan ke layar saat user menakan tombol `KEY_TAB` di mana pada kasus program `EorzeOS`, banyak spasi yang digunakan adalah `4` karakter.

```c
#define BUFFER      128
```
15. Mendefinisikan makro `BUFFER` yang merepresentasikan suatu konstanta di mana dalam penerapannya digunakan untuk mendefinisikan batas maksimum area memori yang digunakan untuk penampungan sementara karakter input yang dimasukkan oleh user melalui function `readString()` yang di mana pada kasus program `EorzeOS` besarnya adalah `127` karakter ditambah dengan satu `\0`.

```C
static unsigned int _xPos = 0, _yPos = 0;
```
16. Mendefinisikan variabel global `_xPos` dan `_yPos` dengan tipe data `unsigned int` yang bersifat statis atau dapat mempertahankan nilai valuenya saat pemanggilan fungsi yang berbeda-beda di mana dalam penerapannya variabel tersebut digunakan merepresentasikan posisi kursor terhadap layar saat ini dalam representasi koordinat (x, y) atau (kolom, baris) di mana pada kasus program `EorzeOS` dimulai pada baris dan kolom dengan indeks `0`.

```c
static unsigned int _xStart = 0, _yStart = 0;
```
17. Mendefinisikan variabel global `_xStart` dan `_yStart` dengan tipe data `unsigned int` yang bersifat statis atau dapat mempertahankan nilai valuenya saat pemanggilan fungsi yang berbeda-beda di mana dalam penerapannya variabel tersebut digunakan merepresentasikan posisi awal kursor terhadap layar dalam representasi koordinat (x, y) atau (kolom, baris) di mana pada kasus program `EorzeOS` terletak pada baris dan kolom dengan indeks `0`. 

```c
static unsigned char _color = 0x0F;
```
18. Mendefinisikan variabel global `_color` dengan tipe data `unsigned char` yang bersifat statis atau dapat mempertahankan nilai valuenya saat pemanggilan fungsi yang berbeda-beda di mana dalam penerapannya variabel tersebut digunakan merepresentasikan atribut warna dari suatu karakter ASCII yang ditampilkan pada layar VGA di mana pada kasus program `EorzeOS` warna yang ditampilkan adalah warna hitam untuk background-nya dan warna putih untuk foreground-nya.

```c
enum KEYCODE {
  KEY_NEWLINE   = '\n',
  KEY_RETURN    = '\r',
  KEY_TAB       = 0x09,
  KEY_BACKSPACE = 0x08
};
```
19. Mendefinisikan enumerasi nama-nama simbolik untuk beberapa `KEYCODE` atau karakter kontrol di mana di antaranya terdiri atas:
	- `KEY_NEWLINE`: yang merepresentasikan karakter `NEWLINE` di mana dalam penerapannya karakter kontrol tersebut digunakan untuk mengindikasikan pemindahan posisi `_yPos` satu baris ke bawah.
	- `KEY_RETURN`: yang merepresentasikan tombol `ENTER` di mana dalam penerapannya karakter kontrol tersebut digunakan untuk mengindikasikan akhir dari suatu proses input pada `BUFFER` menggunakan `readString()` dan mengembalikan posisi `_xPos` kembali ke awal sesuai dengan value yang ditentukan variabel `_xStart`.
	- `KEY_TAB`: yang merepresentasikan tombol `TAB` atau tabulasi horizontal di mana dalam penerapannya karakter tersebut digunakan untuk mengindikasikan penambahan spasi sebanyak `TAB_SIZE` secara horizontal mulai dari di mana kursor berada saat itu.
	- `KEY_BACKSPACE`: yang merepresentasikan tombol `BACKSPACE` di mana dalam penerapannya karakter tersebut digunakan untuk mengindikasikan penghapusan karakter sebelum di mana kursor berada saat itu dan memundurkan posisi kursor tersebut sebanyak satu karakter.

#### • Main

```c
void main() {
	...
}
```
20. Mendeklarasikan function `main()` dengan tipe `void` dan tanpa menggunakan variabel parameter.

```c
clearScreen();
shell();
```
21. Memanggil function `clearScreen()` yang didefinisikan pada program `kernel.c` dan function `shell()` yang didefinisikan pada program `shell.c`.

#### • Reposition X and Y

```c
void repositionXY(unsigned int x, unsigned int y) {
	...
}
```
22. Mendeklarasikan function `repositionXY()` dengan ketentuan parameter:
	- `unsigned int x`: Target koordinat posisi x atau kolom dari layar di mana dalam penerapannya yang akan menjadi value baru dari variabel `_xPos` dan `_xStart`.
 	- `unsigned int y`: Target koordinat posisi y atau baris dari layar di mana dalam penerapannya yang akan menjadi value baru dari variabel `_yPos` dan `_yStart`.

```c
_xPos = x;
...
_xStart = _xPos;
...
```
23. Mengubah value koordinat posisi yang disimpan oleh variabel `_xPos` dan `_xStart` dengan nilai yang ditentukan oleh variabel parameter `x`.

```c
...
_yPos = y;
...
_yStart = _yPos;
```
24. Mengubah value koordinat posisi yang disimpan oleh variabel `_yPos` dan `_yStart` dengan nilai yang ditentukan oleh variabel parameter `y`.

#### • Scroll

```c
void scroll() {
	...
}
```
25. Mendeklarasikan function `scroll()` dengan tipe `void` dan tanpa menggunakan variabel parameter.

```c
unsigned int ax, bx, cx, dx;
```
26. Mendeklarasikan variabel-variabel di mana dalam penerapannya digunakan untuk menyimpan data terkait register yang digunakan di mana di antaranya yaitu register `AX`, `BX`, `CX`, dan `DX` yang merupakan register 16-bit dengan tipe data `unsigned int` untuk menjalankan proses scrolling BIOS menggunakan function `scroll()`.

```c
ax = (SCROLL << 8) | SCROLL_ONE;
```
27. Memasukkan value pada register 16-bit `AX` yang merupakan gabungan antara register 8-bit high byte `AH` di mana dalam penerapannya digunakan sebagai fungsi utama BIOS yang menyimpan value `SCROLL` atau `0x06` yang memungkinkan dilakukannya proses scrolling BIOS dan register 8-bit low byte `AL` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan value `SCROLL_ONE` atau `0x01` yang memuat banyaknya baris yang akan digeser ke atas saat melakukan proses scrolling BIOS.

```c
bx = (_color << 8) | IGNORE;
```
28. Memasukkan value pada register 16-bit `BX` yang merupakan gabungan antara register 8-bit high byte `BH` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan value atribut warna dari suatu karakter ASCII yang ditampilkan pada layar VGA dan register 8-bit low byte `BL` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan value `IGNORE` atau `0x00` yang memuat nomor halaman dari layar saat melakukan proses scrolling BIOS.

```c
cx = (0 << 8) | 0;
```
29. Memasukkan value pada register 16-bit `CX` yang merupakan gabungan antara register 8-bit high byte `CH` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan value batas kiri layar dari proses scrolling BIOS dan register 8-bit low byte `CL` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan value batas atas layar dari proses scrolling BIOS.

```c
dx = ((MAX_ROWS - 1) << 8) | (MAX_COLUMNS - 1);
```
30. Memasukkan value pada register 16-bit `DX` yang merupakan gabungan antara register 8-bit high byte `DH` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan balue batas kanan layar dari proses scrolling BIOS dan register 8-bit low byte `DL` di mana dalam penerapannya digunakan sebagai parameter yang menyimpan value batas bawah layar dari proses scrolling BIOS.

```c
interrupt(INT_VID, ax, bx, cx, dx);
```
31. Memanggil function eksternal `interrupt()` dari program `kernel.asm` di mana dalam penerapannya digunakan untuk menjalankan proses scrolling BIOS terhadap layar dengan menggunakan layanan interupsi video dengan integer `0x10` atau `10h` dan dengan parameter register 16-bit `AX`, `BX`, `CX`, dan `DX`.


```c
repositionXY(0, MAX_ROWS - 1);
```
32. Memanggil function `repositionXY()` untuk mengubah value koordinat posisi x atau kolom menjadi `0` atau kembali ke awal dan koordinat posisi y atau baris menjadi `MAX_ROWS - 1` atau baris terakhir dari layar.

#### • Put Character

```c
void putc(unsigned char c) {
	...
}
```
33. Mendeklarasikan function `putc()` dengan ketentuan parameter:
	- `unsigned char c`: Suatu karakter ASCII yang akan ditampilkan pada layar.

```c
unsigned int offset;
```
34. Mendeklarasikan variabel `offset` dengan tipe data `unsigned int` di mana dalam penerapannya digunakan sebagai acuan letak kursor terhadap layar yang merupakan posisi di mana nantinya akan diletakkan karakter ASCII tersebut.

```c
if (c == 0) {
	return;
}  
```
35. Apabila suatu karakter ASCII yang hendak diletakkan pada layar merupakan karakter dengan nilai ASCII `0` yang merujuk pada karakter `\0`, maka function `putc()` tidak akan meletakkan apapun pada layar. Selain itu, proses function `putc()` tidak akan dilanjutkan dan akan kembali ke tempat di mana function `putc()` dipanggil.

```c
else if (c == KEY_NEWLINE) {
	_xPos = _xStart;
	_yPos++;
	return;
}
```
36. Apabila suatu karakter ASCII yang hendak diletakkan pada layar merupakan karakter `NEWLINE` atau `\n`, maka function `putc()` hanya akan memperbarui kooridinat posisi x atau kolom dan y atau baris dengan ketentuan posisi kolom kembali ke awal sesuai dengan value yang ditentukan variabel `_xStart` dan posisi baris akan bergeser sebanyak satu baris ke bawah. Setelah itu, proses function `putc()` tidak akan dilanjutkan dan akan kembali ke tempat di mana function `putc()` dipanggil.

```c
if (_xPos >= MAX_COLUMNS) {
	_xPos = _xStart;
	_yPos++;
}  
```
37. Apabila setelah suatu karakter ASCII diletakkan pada layar, koordinat posisi x atau kolom melebihi batas maksimum ukuran layar yang didefinisikan oleh makro `MAX_COLUMNS`, maka penempatan karakter ASCII selanjutnya akan bergeser ke bawah sebanyak satu baris dan posisi kolom akan kembali ke awal.

```c
if (_yPos >= MAX_ROWS) {
	scroll();
}  
```
38. Apabila setelah suatu karakter ASCII diletakkan pada layar, koordinat posisi y atau baris melebihi batas maksimum ukuran layar yang didefinisikan oleh makro `MAX_ROWS`, maka function `scroll()` akan dipanggil dan proses scrolling BIOS terhadap layar akan dijalankan.

```c
offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;
```
39. Memasukkan value pada variabel offset yang di mana dalam penerapannya digunakan sebagai acuan letak kursor terhadap layar yang merupakan posisi di mana nantinya akan diletakkan karakter ASCII tersebut di mana proses perhitungan dilakukan dengan penjumlahan alamat offset awal video memori dengan alamat dari koordinat posisi kursor saat function `putc()` dijalankan.

```c
putInMemory(SEGMENT, offset, c);
```
40. Meletakkan karakter ASCII pada layar di mana dalam penerapannya, karakter ASCII tersebut akan diletakkan sesuai dengan alamat segmen video memori yang didefinisikan makro `SEGMENT` dan value offset pada layar sesuai dengan perhitungan yang telah dilakukan sebelumnya.

```c
putInMemory(SEGMENT, offset + 1, _color);
```
41. Meletakkan atribut warna dari karakter ASCII pada layar di mana dalam penerapannya, karakter ASCII tersebut akan diletakkan sesuai dengan alamat segmen video memori yang didefinisikan makro `SEGMENT` dan value offset satu karakter setelah alamat offset yang perhitungannya telah dilakukan sebelumnya, sehingga secara keseluruhan, untuk menampilkan satu karakter beserta atributnya, maka diperlukan ukuran memori sebesar `2` byte.

```c
_xPos++;
```
42. Setelah karakter ASCII diletakkan pada layar, maka koordinat posisi x atau kolom bergeser satu karakter ke kanan. 

#### • Print String

```c
void printString(char *str) {
	...
}
```
43. Mendeklarasikan function `printString()` dengan ketentuan parameter:
	- `char *str`: Suatu pointer dengan tipe data char yang menunjuk pada alamat suatu array string karakter ASCII yang akan ditampilkan pada layar.

```c
if (str == 0) {
	return;
}  
```
44. Apabila array string yang hendak diletakkan pada layar hanya terdiri dari satu karakter dengan nilai ASCII `0` yang merujuk pada karakter `\0`, maka function `printString()` tidak akan memanggil function `putc()`. Selain itu, proses function `printString()` tidak akan dilanjutkan dan akan kembali ke tempat di mana function `printString()` dipanggil.

```c
while(*str) {
	putc(*str);
	str++;
}  
```
45. Selama karakter ASCII yang terdapat pada array string bukan merupakan karakter `\0`, maka function `printString()` akan memanggil function `putc()` dan meletakkan karakter ASCII tersebut pada layar. Proses ini akan berlanjut terus hingga semua karakter ASCII pada array string selain karakter `\0` telah diletakkan pada layar menggunakan function `putc()`.

#### • Read String

```c
void readString(char *buf) {
	...
}
```
46. Mendeklarasikan function `readString()` dengan ketentuan parameter:
	- `char *buf`: Suatu pointer dengan tipe data char yang menunjuk pada array buffer atau alamat suatu area memori yang digunakan untuk penampungan sementara karakter input yang dimasukkan oleh user.

```c
unsigned char c;
```
47. Mendeklarasikan variabel `c` dengan tipe data `unsigned char` di mana dalam penerapannya digunakan untuk menyimpan suatu karakter ASCII yang akan ditampilkan pada layar.

```c
int bufPos = 0;
```
48. Mendeklarasikan variabel `bufPos` dengan tipe data `int` di mana dalam penerapannya digunakan untuk menyimpan indeks dari array buffer atau alamat suatu area memori yang digunakan untuk penampungan sementara karakter input yang dimasukkan oleh user.

```c
unsigned int ax;
```
49. Mendeklarasikan variabel `AX` di mana dalam penerapannya digunakan untuk menyimpan data terkait register 16-bit yang digunakan pada function `readString()` untuk melakukan proses interaksi dengan keyboard seperti membaca input dari user menggunakan function `interrupt()`.

```c
unsigned int offset;
```
50. Mendeklarasikan variabel `offset` dengan tipe data `unsigned int` di mana dalam penerapannya digunakan sebagai acuan letak kursor terhadap layar yang merupakan posisi di mana nantinya akan diletakkan karakter ASCII tersebut.

```c
int i;
```
51. Mendeklarasikan variabel `i` dengan tipe data `int` di mana dalam penerapannya digunakan sebagai indeks proses meletakkan karakter spasi pada layar saat user memasukkan input dengan menekan tombol `TAB` yang pada program `EorzeOS` direpresentasikan dengan variabel `KEY_TAB`.

```c
while (1) {
	...
} 
```
52. Pada kasus program `EorzeOS`, proses membaca input dari user akan berjalan dengan tanpa henti kecuali jika user menekan tombol `ENTER` yang pada program `EorzeOS` direpresentasikan dengan variabel `KEY_RETURN`.

```c
ax = interrupt(INT_KBD, KEYBOARD, 0, 0, 0);
```
53. Memasukkan value yang di mana merupakan value return dari function `interrupt()` setelah melakukan proses interaksi dengan keyboard seperti membaca input dari user dengan menggunakan layanan interupsi keyboard untuk BIOS dengan integer `0x16` atau `16h` ke dalam register 16-bit `AX` yang merupakan gabungan antara register 8-bit high byte `AH` dan register 8-bit low byte `AL`.

```c
c = (unsigned char)(ax & MASK);
```
54. Mengubah tipe data input yang dimasukkan oleh user menjadi tipe data dalam bentuk `unsigned char` di mana dalam penerapannya akan mengambil low byte dari register `AX` yang pada kasus ini merupakan register `AL` yang memuat karakter ASCII dan menghapus high byte dari register `AX` yang pada kasus ini merupakan register `AH`.


```c
if (c == KEY_RETURN) {
	buf[bufPos] = '\0';
	putc(KEY_NEWLINE);
	break;
}
```
55. Apabila karakter ASCII yang terbaca dari input user merupakan karakter `\n` yang pada program `EorzeOS` direpresentasikan dengan variabel `KEY_RETURN` maka ... dan proses membaca input dari user akan dihentikan.

```c
else if (c == KEY_TAB) {
	for (i = 0; i < TAB_SIZE; i++) {
		buf[bufPos] = ' ';
		bufPos++;
		putc(' ');
	}
}  
```
56. Selain itu, apabila karakter ASCII yang terbaca dari input user merupakan karakter `0x09` yang pada program `EorzeOS` direpresentasikan dengan variabel `KEY_TAB` maka pada layar akan diletakkan karakter spasi sesuai dengan value yang disimpan variabel indeks `i` yang telah ditentukan sebelumnya.

```c
else if (c == KEY_BACKSPACE) {
	...      
}  
```
57. Selain itu, apabila karakter ASCII yang terbaca dari input user merupakan karakter `0x08` yang pada program `EorzeOS` direpresentasikan dengan variabel `KEY_BACKSPACE` maka akan diberlakukan penghapusan karakter ASCII yang ada pada layar di mana pada penerapannya terdapat beberapa kasus tertentu yang perlu menggunakan penanganan khusus.

```c
if (bufPos > 0) {
	bufPos--;
	...
}  
```
58. Suatu karakter ASCII yang ditampilkan pada layar hanya akan dihapus jika benar-benar ada dan terdapat di dalam array buffer. Apabila terindikasi bahwa terdapat karakter pada layar, maka indeks array buffer akan dikurangi satu yang menandakan bahwa karakter ASCII yang terakhir ditampilkan pada layar akan dihapus.

```c
if (_xPos > _xStart) {
	_xPos--;
}  
```
59. Selain itu, selama nilai value dari variabel `_xPos` di mana dalam penerapannya digunakan untuk menyimpan data terkait koordinat posisi x atau kolom yang menyimpan value kolom letak karakter ASCII terakhir yang ditampilkan pada layar tidak kurang dari nilai value variabel `_xStart` di mana dalam penerapannya digunakan untuk menyimpan data terkait koordinat posisi x atau kolom awal, maka koordinat posisi x atau kolom yang menyimpan value kolom letak karakter ASCII terakhir yang ditampilkan pada layar akan dikurangi satu yang menandakan bahwa karakter ASCII yang terakhir ditampilkan pada layar akan dihapus.

```c
else if (_yPos > _yStart) {
	_yPos--;
	_xPos = MAX_COLUMNS - 1;
}  
```
60. Selain itu, selama nilai value dari variabel `_yPos` di mana dalam penerapannya digunakan untuk menyimpan data terkait koordinat posisi y atau baris yang menyimpan value baris letak karakter ASCII terakhir yang ditampilkan pada layar tidak kurang dari nilai value variabel `_yStart` di mana dalam penerapannya digunakan untuk menyimpan data terkait koordinat posisi y atau baris awal, maka koordinat posisi y atau baris yang menyimpan value baris letak karakter ASCII terakhir yang ditampilkan pada layar akan dikurangi satu dan variabel `_xPos` di mana dalam penerapannya digunakan untuk menyimpan data terkait koordinat posisi x atau kolom yang menyimpan value kolom letak karakter ASCII terakhir yang ditampilkan pada layar akan diubah menjadi koordinat posisi x atau kolom terakhir dari satu baris di atas di mana variabel `_yPos` merujuk sebelum dilakukan pengurangan.

```c
offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;
```
61. Memasukkan value pada variabel offset yang di mana dalam penerapannya digunakan sebagai acuan letak kursor terhadap layar yang merupakan posisi di mana nantinya akan diletakkan karakter ASCII tersebut di mana proses perhitungan dilakukan dengan penjumlahan alamat offset awal video memori dengan alamat dari koordinat posisi kursor saat function `readString()` dijalankan.
```c
putInMemory(SEGMENT, offset, ' ');
```
62. Meletakkan karakter ASCII pada layar di mana pada kasus proses penghapusan karakter, karakter yang diletakkan adalah karakter spasi dan dalam penerapannya, karakter spasi tersebut akan diletakkan sesuai dengan alamat segmen video memori yang didefinisikan makro `SEGMENT` dan value offset pada layar sesuai dengan perhitungan yang telah dilakukan sebelumnya.

```c
putInMemory(SEGMENT, offset + 1, _color);
```
63. Meletakkan atribut warna dari karakter ASCII pada layar di mana pada kasus proses penghapusan karakter, karakter yang diletakkan adalah karakter spasi dan di mana dalam penerapannya, karakter spasi tersebut akan diletakkan sesuai dengan alamat segmen video memori yang didefinisikan makro `SEGMENT` dan value offset satu karakter setelah alamat offset yang perhitungannya telah dilakukan sebelumnya, sehingga secara keseluruhan, untuk menampilkan satu karakter beserta atributnya, maka diperlukan ukuran memori sebesar `2` byte.

```c
else {
	if (c >= VALID_ASCII && bufPos < BUFFER - 1) {
		buf[bufPos] = c;
		bufPos++;
		putc(c);
	}  
}  
```
64. Selain itu, apabila karakter ASCII yang terbaca dari input user merupakan suatu karakter yang berada di dalam batasan yang didefinisikan makro `VALID_ASCII`, maka pada layar akan diletakkan karakter ASCII sesuai dengan nilai value yang disimpan pada variabel `c`. Setelah itu, variabel `bufPos` di mana dalam penerapannya digunakan untuk menyimpan value indeks dari array buffer atau alamat suatu area memori yang digunakan untuk penampungan sementara karakter input yang dimasukkan oleh user akan ditambahkan satu.

#### • Clear Screen

```c
void clearScreen() {
	...
}
```
65. Mendeklarasikan function `clearScreen()` dengan tipe `void` dan tanpa menggunakan variabel parameter.

```c
unsigned int offset;
```
66. Mendeklarasikan variabel `offset` dengan tipe data `unsigned int` di mana dalam penerapannya digunakan sebagai acuan letak kursor terhadap layar yang merupakan posisi di mana nantinya akan diletakkan karakter ASCII tersebut.

```c
int i, j;
```
67. Mendeklarasikan variabel `i` dan `j` dengan tipe data `int` di mana dalam penerapannya digunakan sebagai indeks yang merujuk pada koordinat posisi suatu kolom dan baris pada layar.

```c
for (i = 0; i < MAX_ROWS; i++) {
	for (j = 0; j < MAX_COLUMNS; j++) {
		...
	}  
}  
```
68. Pada layar, dimulai dengan koordinat posisi dengan nilai `0` atau posisi awal, program akan berjalan menelusuri satu karakter ASCII demi satu karakter ASCII sepanjang layar di mana variabel `i` akan bergerak dari atas ke bawah secara vertikal dan variabel `j` akan bergerak dari kiri ke kanan secara horizontal selama koordinat posisi tidak melebihi ukuran layar yang telah ditentukan di mana pada kasus program `EorzeOS` merupakan nilai value yang didefinisikan oleh makro `MAX_ROWS` dan `MAX_COLUMNS`.

```c
offset = ADDRESS + (_yPos * MAX_COLUMNS + _xPos) * 2;
```
<!-- 🤨 -->
69. Memasukkan value pada variabel offset yang di mana dalam penerapannya digunakan sebagai acuan letak kursor terhadap layar yang merupakan posisi di mana nantinya akan diletakkan karakter ASCII tersebut di mana proses perhitungan dilakukan dengan penjumlahan alamat offset awal video memori dengan alamat dari koordinat posisi kursor saat function `readString()` dijalankan.
```c
putInMemory(SEGMENT, offset, ' ');
```
70. Meletakkan karakter ASCII pada layar di mana pada kasus proses penghapusan karakter, karakter yang diletakkan adalah karakter spasi dan dalam penerapannya, karakter spasi tersebut akan diletakkan sesuai dengan alamat segmen video memori yang didefinisikan makro `SEGMENT` dan value offset pada layar sesuai dengan perhitungan yang telah dilakukan sebelumnya.

```c
putInMemory(SEGMENT, offset + 1, _color);
```
71. Meletakkan atribut warna dari karakter ASCII pada layar di mana pada kasus proses penghapusan karakter, karakter yang diletakkan adalah karakter spasi dan di mana dalam penerapannya, karakter spasi tersebut akan diletakkan sesuai dengan alamat segmen video memori yang didefinisikan makro `SEGMENT` dan value offset satu karakter setelah alamat offset yang perhitungannya telah dilakukan sebelumnya, sehingga secara keseluruhan, untuk menampilkan satu karakter beserta atributnya, maka diperlukan ukuran memori sebesar `2` byte.

```c
repositionXY(0, 0);
```
72. Memanggil function `repositionXY()` untuk mengubah value koordinat posisi x atau kolom menjadi `0` atau kembali ke awal dan koordinat posisi y atau baris menjadi `0` atau kembali ke awal.

### • Standard Library

<p align="justify">  
&emsp;&emsp;Pada program <code>EorzeOS</code>, agar program <code>shell.c</code> yang berinteraksi dengan user secara top-level dalam penerapan logikanya dapat berjalan, maka dibutuhkan beberapa fungsi untuk membantu menyederhanakan program <code>shell.c</code> tersebut. Maka dari itu, dibuatlah suatu program dengan bahasa ANSI C (C89) dengan nama <code>std_lib.c</code> di mana dalam penerapannya dapat menyimpan deklarasi fungsi utilitas yang banyak digunakan oleh <code>shell.c</code> dengan fungsi utilitas yang dimaksud dan digunakan dalam program <code>std_lib.c</code> adalah fungsi-fungsi yang berkaitan dengan manipulasi dan konversi tipe suatu variabel beserta tipe datanya dan nilai value yang tersimpan di dalam variabel tersebut. 
</p>

Adapun tampilan `std_lib.c` secara keseluruhan adalah sebagai berikut:

```c
#include "std_lib.h"
#include "std_type.h"

#define INT_MAX 32767

int div(int a, int b) {
  int quotient = 0;
  int negative = false;
  int tmpb, multiple;

  if (b == 0) {
    return INT_MAX;
  }

  if (a < 0) {
    a *= -1;
    negative = !negative;
  }
  
  if (b < 0) {
    b *= -1;
    negative = !negative;
  }

  while (a >= b) {
    tmpb = b;
    multiple = 1;

    while ((tmpb << 1) > 0 && (tmpb << 1) <= a) {
      tmpb <<= 1;
      multiple <<= 1;
    }

    a -= tmpb;
    quotient += multiple;
  }

  if (negative) {
    return -quotient;
  }

  return quotient;
}

int mod(int a, int b) {
  int negative = false;
  int tmpb;

  if (b == 0) {
    return 0;
  }

  if (a < 0) {
    a *= -1;
    negative = true;
  }

  if (b < 0) {
    b *= -1;
  }

  while (a >= b) {
    tmpb = b;

    while ((tmpb << 1) > 0 && (tmpb << 1) <= a) {
      tmpb <<= 1;
    }

    a -= tmpb;
  }

  if (negative) {
    return -a;
  }

  return a;
}

int strcmp(char* str1, char* str2) {
	int res = 0;
	while (!(res = *(unsigned char*)str1 - *(unsigned char*)str2) && *str2) {
		++str1, ++str2;
  }

	if (res < 0) {
		res = -1;
  }
	if (res > 0) {
		res = 1;
  }

	return res;
}

char *strcpy(char *dst, char *src) {
  char *dstPtr = dst;

  while (*src != '\0') {
    *dst = *src;
    dst++;
    src++;
  }
  
  *dst = '\0';

  return dstPtr;
}

void clear(byte *buf, unsigned int size) {
  unsigned int i;
  for (i = 0; i < size; i++) {
    buf[i] = 0;
  }
}

void atoi(char *str, int *num) {
  int tbuf[12];
  int pos = 0;
  int is_negative = 0;
  *num = 0;

  if (str[0] == '0' && str[1] == '\0') {
    return;
  }

  if(str[0] == '-') {
    is_negative = 1;
    pos++;
  }
  
  for (pos; str[pos] != '\0'; pos++) {
    if (str[pos] >= '0' && str[pos] <= '9') {
      *num = (*num * 10) + (str[pos] - '0');
    }
    else {
      break;
    }
  }

  if (is_negative) {
    *num *= -1; 
  }
}

void itoa(int num, char *str) {
  char tbuf[12];
  int pos = 0;
  int is_negative = 0;
  int i, len;

  if (num == 0) {
    str[0] = '0';
    str[1] = '\0';
    return;
  }

  if (num < 0) {
    num *= -1;
    is_negative = 1;
  }

  while (num != 0) {
    tbuf[pos] = (char)('0' + mod(num, 10));
    pos++;
    num = div(num, 10);
  }

  if (is_negative) {
    tbuf[pos] = '-';
    pos++;
  }

  len = pos;

  for (i = 0; i < len; i++) {
    str[i] = tbuf[len - 1 - i];
  }

  str[len] = '\0';
}
```

Di mana langkah implementasinya:

#### • Preprocessors

```c
#include "std_lib.h"
#include "std_type.h"
```
1. Menyertakan file-file header yang didefinisikan pada direktori `/include` di mana file header tersebut menyediakan elemen seperti deklarasi fungsi, makro, beserta definisi konstanta yang diperlukan dalam implementasi program `std_lib.c`.

#### • Integer Division

```c
int div(int a, int b) {
	...
}
```
2. Mendeklarasikan function `div()` dengan ketentuan parameter:
	- `int a`: Suatu integer yang merupakan angka pembilang dari proses pembagian dua bilangan.
 	- `int b`: Suatu integer yang merupakan angka penyebut dari proses pembagian dua bilangan.

```c
int quotient = 0;
```
3. Mendeklarasikan variabel `quotient` dengan tipe data `int` di mana dalam penerapannya digunakan sebagai variabel yang menyimpan data hasil bagi dari proses pembagian antara nilai value variabel `a` dengan nilai value variabel `b`.

```c
int negative = false;
```
4. Mendeklarasikan variabel `negative` dengan tipe data `int` di mana dalam penerapannya digunakan sebagai variabel boolean untuk menyimpan data apakah suatu pembagian dapat menghasilkan bilangan negatif atau tidak.


```c
int tmpb;
```
5. Mendeklarasikan variabel `tmpb` dengan tipe data `int` di mana dalam penerapannya digunakan untuk variabel sementara yang menyimpan nilai value yang disimpan oleh variabel `b` yang nantinya akan digunakan untuk operasi pembagian menggunakan metode penggeseran biner.

```c
```
5. 

#### • Integer Modulus
#### • Compare Strings
#### • Copy Strings
#### • Clear Buffer Input
#### • ASCII to Integer
#### • Integer to ASCII

### • Shell

<p align="justify">  
&emsp;&emsp;Pada program <code>EorzeOS</code>, dibutuhkan suatu program yang di mana pada dasarnya, dapat berinteraksi secara langsung dengan seorang user secara top-level melalui perantara Command Line Interface atau CLI berbasis teks. Maka dari itu, dibuatlah program dengan nama <code>shell.c</code> sebagai perantara antara user dengan program low-level seperti <code>kernel.c</code> di mana dalam penerapannya digunakan sebagai program di mana user memasukkan suatu perintah atau input yang nantinya akan digunakan oleh program <code>EorzeOS</code> sebagai dasar dari dilakukannya processing di mana hasilnya nanti akan dikembalikan lagi ke user ke dalam bentuk suatu keluaran output yang dicetak pada layar.
</p>

Adapun tampilan `shell.c` secara keseluruhan adalah sebagai berikut:

```c
#include "shell.h"
#include "std_lib.h"
#include "kernel.h"

#define MAX_HISTORY 20
#define BUFFER_SIZE 128

char current_user[64] = "user";
char history[MAX_HISTORY][BUFFER_SIZE];
int history_count = 0;

void shell() {
    char buf[BUFFER_SIZE];
    char original_input[BUFFER_SIZE];
    char cmd[64];
    char args[10][64];
    int arg_count;
    int num1, num2;
    int resint;
    char resstr[12];

    printString("Welcome to EorzeOS!\n");
    
    while (true) {
        clear(buf, BUFFER_SIZE);
        printString(current_user);
        printString("> ");

        readString(buf);
        strcpy(original_input, buf);

        // Simpan ke history (jika tidak kosong)
        if (buf[0] != '\0') {
            if (history_count < MAX_HISTORY) {
                strcpy(history[history_count++], buf);
            } else {
                // Geser seluruh history ke bawah, buang index 0, tambahkan di akhir
                int i;
                for (i = 0; i < MAX_HISTORY-1; i++) {
                    strcpy(history[i], history[i+1]);
                }
                strcpy(history[MAX_HISTORY-1], buf);
            }
        }

        parseCommand(buf, cmd, args, &arg_count);

        if (cmd[0] == '\0') continue;

        // exit / quit
        if (strcmp(cmd, "exit") == 0 || strcmp(cmd, "quit") == 0) {
            printString("Bye, ");
            printString(current_user);
            printString("!\n");
            break;
        }
        // help
        else if (strcmp(cmd, "help") == 0) {
            printString("Available commands:\n");
            printString("   user [name]     : Change current username\n");
            printString("   history         : Show last commands\n");
            printString("   yo              : Print 'gurt'\n");
            printString("   gurt            : Print 'yo'\n");
            printString("   add             : Add two integers\n");
            printString("   sub             : Subtract two integers\n");
            printString("   mul             : Multiply two integers\n");
            printString("   div             : Divide two integers\n");
            printString("   exit/quit       : Exit shell\n");
            printString("   help            : Show this message\n");
            printString("   (else)          : Echo input\n");
        }
        // user
        else if (strcmp(cmd, "user") == 0) {
            if (arg_count >= 1 && args[0][0] != '\0') {
                strcpy(current_user, args[0]);
                printString("Username changed to ");
                printString(current_user);
            } else {
                strcpy(current_user, "user");
                printString("Username changed to user");
            }
            printString("\n");
        }
        // history
        else if (strcmp(cmd, "history") == 0) {
            int i;
            for (i = 0; i < history_count; i++) {
                printString(history[i]);
                printString("\n");
            }
        }
        // yo dan gurt
        else if (strcmp(cmd, "yo") == 0) {
            printString("gurt\n");
        } else if (strcmp(cmd, "gurt") == 0) {
            printString("yo\n");
        }
        else if (strcmp(cmd, "div") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = div(num1, num2);
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "add") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = num1 + num2;
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "mul") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = num1 * num2;
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "sub") == 0) {
            atoi(args[0], &num1);
            atoi(args[1], &num2);
            resint = num1 - num2;
            itoa(resint, resstr);
            printString(resstr);
            printString("\n");
        }
        else if (strcmp(cmd, "grandcompany") == 0) {
            clearScreen();
            if (strcmp(args[0], "maelstrom") == 0) {
                putInMemory(0xB000, 0x8000 * 2 + 1, 0x04);
            }
            else if (strcmp(args[0], "twinadder") == 0) {
                putInMemory(0xB000, 0x8000 * 2 + 1, 0x0E);
            }
            else if (strcmp(args[0], "immortalflames") == 0) {
                putInMemory(0xB000, 0x8000 * 2 + 1, 0x01);
            }
            else {
                putInMemory(0xB000, 0x8000 * 2 + 1, 0x0F);
            }
        }
        // else echo
        else {
            printString(original_input);
            printString("\n");
        }
    }
}

void parseCommand(char *buf, char *cmd, char arg[10][64], int *arg_count) {
    int i = 0, j = 0, k;
    *arg_count = 0;

    // Lewati spasi awal
    while (buf[i] != '\0' && buf[i] == ' ') i++;

    // Baca cmd
    j = 0;
    while (buf[i] != '\0' && buf[i] != ' ' && j < 63) {
        cmd[j++] = buf[i++];
    }
    cmd[j] = '\0';

    // Lewati spasi sebelum arg
    while (buf[i] != '\0' && buf[i] == ' ') i++;

    // Baca argumen sebanyak mungkin (maks 9, sisanya diabaikan)
    for (k = 0; k < 10; k++) {
        int m = 0;
        if (buf[i] == '\0' || *arg_count >= 9) {
            arg[k][0] = '\0';
            continue;
        }
        while (buf[i] != '\0' && buf[i] != ' ' && m < 63) {
            arg[k][m++] = buf[i++];
        }
        arg[k][m] = '\0';
        (*arg_count)++;

        while (buf[i] != '\0' && buf[i] == ' ') i++;
    }
}
```

Di mana langkah implementasinya:

### • Makefile

<p align="justify">
&emsp;&emsp;Makefile merupakan sebuah file yang memiliki fungsi utama menuliskan daftar instruksi yang digunakan untuk menyederhanakan proses build dan compile program <code>EorzeOS</code> yang cenderung memiliki banyak command yang perlu dijalankan agar dapat dieksekusi. Makefile akan hanya menjalankan bagian instruksi yang diperlukan dan tidak akan menjalankan instruksi yang memiliki keluaran yang sudah ada dan tidak berubah dari proses build sebelumnya.  
</p>

Adapun tampilan file makefile yang digunakan pada program `EorzeOS` ini adalah sebagai berikut:

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

#### • Global Variables

```make
ASM		= nasm
```
1. Variabel `ASM` menyimpan data terkait compiler yang pada kasus ini adalah `Netwide Assembler` atau disingkat `nasm` dan digunakan untuk proses mengubah kode bahasa assembly menjadi suatu file dengan format raw binary yang dapat dieksekusi oleh processor.

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

#### • Target and Rule

```make
prepare:
	dd if=/dev/zero of=$(FLOPPY_IMG) bs=512 count=2880
```
19. Mendefinisikan target `prepare` yang di dalamnya terdapat suatu rule yang menjalankan program `dd` yang merupakan suatu utilitas bawaan UNIX yang digunakan untuk menyalin dan mengubah data dengan format low-level, menyalin null byte atau `0x00` dari input file `/dev/zero` ke dalam floppy image yang berada pada di mana variabel `FLOPPY_IMG` merujuk dengan ketentuan banyaknya adalah `2880` sektor, di mana masing-masing sektor memiliki ukuran sebesar `512` byte.

```make
bootloader:
	$(ASM) -f bin $(BOOTLOADER_SRC) -o $(BOOTLOADER_BIN)
	...
```
20. Mendefinisikan target `bootloader` yang di dalamnya terdapat beberapa rule di mana yang pertama memiliki fungsi untuk menjalankan program `nasm` untuk melakukan proses compile file kode bahasa assembly yang tersimpan pada di mana variabel `BOOTLOADER_SRC` merujuk dan mengubahnya ke dalam file dengan format raw binary yang dapat dieksekusi oleh processor di mana pada kasus ini file tersebut tersimpan pada file di mana variabel `BOOTLOADER_BIN` merujuk.


```make
...
	...
	dd if=$(BOOTLOADER_BIN) of=$(FLOPPY_IMG) bs=512 count=1 conv=notrunc
```
21. Setelah file kode bahasa assembly yang tersimpan pada di mana variabel `BOOTLOADER_SRC` merujuk tercompile dan file keluarannya tersimpan pada variabel `BOOTLOADER_BIN`, maka akan dijalankan program selanjutnya di mana program `dd` akan menyalin isi dari di mana variabel `BOOTLOADER_BIN` merujuk ke dalam floppy image yang berada pada di mana variabel `FLOPPY_IMG` merujuk dengan ketentuan banyaknya adalah satu sektor yaitu sektor `0` yang memiliki ukuran `512` byte dan program juga akan memastikan bahwa floppy image keluaran program `dd` tidak akan ter-truncate yang mengakibatkan floppy image hanya memiliki ukuran yang besarnya sama dengan sektor `0` sehingga sektor selanjutnya masih utuh dan tidak terpotong untuk nantinya dapat digunakan untuk memasukkan file kernel program `EorzeOS`.

```make
stdlib:
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(STDLIB_C_SRC) -o $(STDLIB_C_OBJ)
```
22. Mendefinisikan target `stdlib` yang di dalamnya terdapat suatu rule yang menjalankan program `bcc` yang digunakan untuk melakukan proses compile file kode bahasa ANSI C (C89) yang terletak pada di mana variabel `STDLIB_C_SRC` merujuk dengan menyertakan file-file header yang tersimpan pada direktori `/include` ke dalam bentuk file objek di mana nantinya akan tersimpan pada di mana variabel `STDLIB_C_OBJ` merujuk.

```make
shell:
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(SHELL_C_SRC) -o $(SHELL_C_OBJ)
```
23. Mendefinisikan target `shell` yang di dalamnya terdapat suatu rule yang menjalankan program `bcc` yang digunakan untuk melakukan proses compile file kode bahasa ANSI C (C89) yang terletak pada di mana variabel `SHELL_C_SRC` merujuk dengan menyertakan file-file header yang tersimpan pada direktori `/include` ke dalam bentuk file objek di mana nantinya akan tersimpan pada di mana variabel `SHELL_C_OBJ` merujuk.

```make
kernel:
	$(ASM) -f as86 $(KERNEL_ASM_SRC) -o $(KERNEL_ASM_OBJ)
	...
```
24. Mendefinisikan target `kernel` yang di dalamnya terdapat beberapa rule di mana yang pertama memiliki fungsi untuk menjalankan program `nasm` untuk melakukan proses compile file kode bahasa assembly yang tersimpan pada di mana variabel `KERNEL_ASM_SRC` merujuk dan mengubahnya ke dalam file objek di mana pada kasus ini file tersebut tersimpan pada file di mana variabel `KERNEL_ASM_OBJ` merujuk.

```make
...
	...
	$(CC) -I$(INCLUDE_PATH) -ansi -c $(KERNEL_C_SRC) -o $(KERNEL_C_OBJ)
	...
```
25. Setelah file kode bahasa assembly yang tersimpan pada di mana variabel `KERNEL_ASM_SRC` merujuk tercompile dan file keluarannya tersimpan pada di mana variabel `KERNEL_ASM_OBJ` merujuk, maka akan dijalankan program selanjutnya di mana program `bcc` akan melakukan proses compile file kode bahasa ANSI C (C89) yang terletak pada di mana variabel `KERNEL_C_SRC` merujuk dengan menyertakan file-file header yang tersimpan pada direktori `/include` ke dalam bentuk file objek di mana nantinya akan tersimpan pada di mana variabel `KERNEL_C_OBJ` merujuk.

```make
...
	...
	$(LINKER) -o $(KERNEL_BIN) -d $(KERNEL_C_OBJ) $(KERNEL_ASM_OBJ) $(SHELL_C_OBJ) $(STDLIB_C_OBJ)
```
26. Setelah file kode bahasa ANSI C (C89) yang tersimpan pada di mana variabel `KERNEL_C_SRC` merujuk tercompile dan file keluarannya tersimpan pada di mana variabel `KERNEL_C_OBJ` merujuk, maka akan dijalankan program selanjutnya di mana program `ld86` akan melakukan proses penggabungan file-file objek program ANSI C (C89) yang telah di-compile oleh `bcc` menjadi suatu file biner yang di mana nantinya akan tersimpan pada di mana variabel `KERNEL_BIN` merujuk.

```make
link:
	dd if=$(KERNEL_BIN) of=$(FLOPPY_IMG) bs=512 seek=1 conv=notrunc
```
27. Mendefinisikan target `link` yang di dalamnya terdapat suatu rule yang menjalankan program `dd` yang akan akan menyalin isi dari di mana variabel `KERNEL_BIN` merujuk ke dalam floppy image yang berada pada di mana variabel `FLOPPY_IMG` merujuk dengan ketentuan seek atau dimulai dari sektor `1` dan akan memenuhi sektor-sektor selanjutnya yang masing-masing memiliki ukuran `512` byte hingga file kernel sepenuhnya dapat dimasukkan ke dalam floppy image. Selain itu, program juga akan memastikan bahwa floppy image keluaran program `dd` tidak akan ter-truncate yang mengakibatkan floppy image hanya memiliki ukuran yang besarnya sama dengan besar file bootloader dan kernel sehingga sektor selanjutnya masih utuh dan tidak terpotong.

```make
build: prepare bootloader stdlib shell kernel link
	$(EMULATOR) -f $(EMULATOR_SRC)
```
28. Mendefinisikan target utama `build` yang akan menjalankan target-target yang dicantumkan secara berurutan. Selain itu, juga di dalamnya terdapat suatu rule yang menjalankan program `bochs` yang akan menjalankan emulator untuk virtualisasi program `EorzeOS` yang sudah utuh dengan menggunakan file konfigurasi `bochsrc.txt` sebagai acuannya.

### • Kendala yang Dialami

<p align="center">
	<img src="https://github.com/user-attachments/assets/c7c7e1c3-ad57-4980-922f-324e3f34be4a" alt="Kangen melempar sebuah error ke stderr">  
</p>

> (1) Screenshot potret munculnya dua hieroglif pada layar emulator Bochs.

<p align="justify">
&emsp;&emsp;Permasalahan yang ditampilkan pada potret merupakan suatu kasus di mana pada saat melakukan uji coba function <code>putc()</code> pada program <code>kernel.c</code> dengan mencoba untuk menampilkan satu karakter ASCII '<code>X</code>', pada emulator Bochs, karakter ASCII tersebut tidak muncul melainkan terdapat dua hieroglif yang ditampilkan pada layar. Hal ini dikarenakan pada program ANSI C (C89) yang menggunakan sistem 16-bit dengan compiler <code>bcc</code>, urutan pendeklarasian fungsi pada program mempengaruhi kinerja program tersebut. Di mana pada kasus permasalahan di atas, disebabkan oleh penempatan function <code>main()</code> pada bagian terakhir dari program <code>kernel.c</code> dan bukan merupakan function yang dideklarasikan paling awal.
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/3c6066dc-0ee6-4c6b-95d0-2d7b14e4ca3d" alt="Brain Damage 3?" width="640" height="360">  
</p>

> (2) Screenshot potret error saat proses compiling program `EorzeOS` di mana compiler tidak dapat menemukan file header `std_lib.h`.

<p align="justify">
&emsp;&emsp;Permasalahan yang ditampilkan pada potret merupakan suatu kasus di mana pada saat mencoba untuk melakukan proses compile program <code>shell.c</code> dengan mengikutsertakan file header <code>std_lib.h</code> menyebabkan error di mana compiler tidak dapat menemukan file header <code>std_lib.h</code> yang diikutsertakan. Hal ini dikarenakan pada program ANSI C (C89) yang menggunakan sistem 16-bit dengan compiler <code>bcc</code>, urutan pendeklarasian file header pada program mempengaruhi kinerja program tersebut. Di mana pada kasus permasalahan di atas, disebabkan oleh file header <code>kernel.h</code> dideklarasikan terlebih dahulu dibandingkan dengan file header <code>std_lib.h</code>. Hal ini menyebabkan compiler tidak dapat membaca file header <code>std_lib.h</code> tersebut walaupun sebelumnya compiler dapat membaca file header <code>kernel.h</code> yang terletak di direktori yang sama.
</p>

<p align="center">
	<img src="https://github.com/user-attachments/assets/cd19ef91-11a1-46a7-8c75-7cdda6289fd5" alt="user_cant_think_of_any_hidden_text_ideas_no_more()" width="640" height="360">  
</p>

> (3) Screenshot potret proses compiling program `EorzeOS` berhasil jika file header `std_lib.h` didefinisikan terlebih dahulu dibandingkan dengan `kernel.h`.

### • Revisi
1. Implementasi Fitur `Grand Company` (Personalisasi Terminal)  
   1.1.Tujuan Fitur
   Fitur ini memungkinkan pengguna untuk "bergabung" dengan salah satu dari tiga Grand Company di Eorzea, yang akan mengubah warna latar belakang terminal dan judul prompt pengguna.  
   1.2 Detail Implementasi
   - Variabel Judul Grand Company: Variabel global `current_grandcompany` di `src/shell.c` menyimpan judul Grand Company yang akan ditambahkan ke `prompt`.
	```c
	// src/shell.c
	char current_user[64] = "user";
	char current_grandcompany[64] = ""; // Kosong secara default
	```
    - Pembaruan Prompt: Di awal loop `while(true)` di `shell()`, prompt pengguna diperbarui untuk mencakup `@<GrandCompanyTitle>` jika `current_grandcompany` tidak kosong.
	```c
	// src/shell.c (dalam fungsi shell())
	// ...
	        printString(current_user);
	        if (current_grandcompany[0] != '\0') {
	            printString("@");
	            printString(current_grandcompany);
	        }
	        printString("> ");
	// ...
	```
     - Perintah `grandcompany`: Perintah ini memproses argumen nama Grand Company. Berdasarkan nama yang valid `(maelstrom, twinadder, immortalflames)`, terminal akan dihapus `(clearScreen())`, warna teks diubah menggunakan `setColor()`, dan `current_grandcompany` diatur. Jika argumen tidak valid, pesan error ditampilkan.
	```c
	// src/shell.c (dalam fungsi shell())
	        else if (strcmp(cmd, "grandcompany") == 0) {
	            if (arg_count >= 1 && args[0][0] != '\0') {
	                if (strcmp(args[0], "maelstrom") == 0) {
	                    clearScreen();
	                    setColor(0x0C); // Merah terang
	                    strcpy(current_grandcompany, "Storm");
	                } else if (strcmp(args[0], "twinadder") == 0) {
	                    clearScreen();
	                    setColor(0x0E); // Kuning terang
	                    strcpy(current_grandcompany, "Serpent");
	                } else if (strcmp(args[0], "immortalflames") == 0) {
	                    clearScreen();
	                    setColor(0x09); // Biru terang
	                    strcpy(current_grandcompany, "Flame");
	                } else {
	                    printString("Error: Grand company tidak dikenal.\n");
	                    printString("Gunakan maelstrom, twinadder, atau immortalflames.\n");
	                }
	            } else {
	                printString("Error: Nama grand company tidak diberikan.\n");
	                printString("Gunakan grandcompany [nama].\n");
	            }
	        }
	```
	- Perintah clear (untuk reset): Perintah clear ditambahkan untuk mereset terminal ke warna default (putih) dan menghapus judul Grand Company.
	```c
	// src/shell.c (dalam fungsi shell())
	        else if (strcmp(cmd, "clear") == 0) {
	            clearScreen();
	            setColor(0x0F); // Kembali ke putih terang
	            strcpy(current_grandcompany, ""); // Hapus nama grand company
	            printString("Para Grand Company sedih kamu netral.\n");
	        }
	```
 	- Fungsi `setColor()`: Fungsi ini diimplementasikan di `src/kernel.c` untuk mengubah variabel `statis _color` di kernel yang mengontrol atribut warna karakter yang akan dicetak. Deklarasi fungsi ini ditambahkan di `include/kernel.h`.
	```c
	// include/kernel.h
	void setColor(unsigned char color); // Deklarasi
	```
	```c
	// src/kernel.c
	// ...
	static unsigned char _color = 0x0F; // Variabel warna di kernel
	
	// Implementasi fungsi
	void setColor(unsigned char color) {
	    _color = color;
	}
	// ...
	```
2. Implementasi Fitur Respons Acak `(yogurt)`
   2.1 Tujuan Fitur  
   Fitur ini bertujuan untuk membuat perintah yogurt merespons secara dinamis dan tidak terduga dari sekumpulan pilihan yang telah ditentukan, yaitu `"yo"`, `"ts unami gng </3"`, dan `"sygau"`. Output respons juga diharapkan diawali dengan `"gurt> "` untuk konsistensi tampilan.
   2.2 Detail Implementasi
   - Definisi Respons: Array string global `yogurt_responses` digunakan untuk menyimpan daftar respons yang mungkin. Variabel `num_yogurt_responses` menyimpan jumlah respons dalam array. Penempatan di global scope `(src/shell.c)` diperlukan untuk kompatibilitas dengan standar `C89` `(bcc)`.
	```c
	// src/shell.c
	// ...
	#define BUFFER_SIZE 128
	
	char current_user[64] = "user";
	char history[MAX_HISTORY][BUFFER_SIZE];
	int history_count = 0;
	
	// Dipindahkan ke global/static agar bisa diinisialisasi di C89
	char *yogurt_responses[] = {
	    "yo",
	    "ts unami gng </3",
	    "sygau"
	};
	int num_yogurt_responses = 3;
	// ...
	```
 	- Pemilihan Respons Acak: Di dalam fungsi `shell()`, ketika perintah yogurt terdeteksi, sebuah indeks acak dihasilkan menggunakan fungsi `rand()` dan `mod()` kustom. Respons yang sesuai kemudian dicetak.
	```c
	// src/shell.c (dalam fungsi shell())
	        // yogurt - Fitur baru!
	        else if (strcmp(cmd, "yogurt") == 0) {
	            random_index = mod(rand(), num_yogurt_responses); 
	            printString("gurt> "); // Menambahkan awalan "gurt> "
	            printString(yogurt_responses[random_index]);
	            printString("\n");
	        }
	```
	- Dukungan Generator Angka Acak `(rand()`, `srand())`: Karena lingkungan OS minimal tidak memiliki pustaka C standar penuh, implementasi `rand()` dan `srand()` kustom diperlukan di `src/std_lib.c` dan dideklarasikan di `include/std_lib.h.` `srand(1)` dipanggil di `main()` `(src/kernel.c)` untuk menginisialisasi seed.
	```c
	// include/std_lib.h
	int rand();
	void srand(unsigned int seed);
	```
	```c
	// src/std_lib.c
	static unsigned int next_rand_seed = 1;
	
	void srand(unsigned int seed) {
	    next_rand_seed = seed;
	}
	
	int rand() {
	    next_rand_seed = (next_rand_seed * 25173 + 13849); // LCG 16-bit
	    return (int)(next_rand_seed >> 1) & 0x7FFF; // Hasil 0-32767
	}
	```
	```c
	// src/kernel.c (dalam fungsi main())
	void main() {
	  clearScreen();
	  srand(1); // Inisialisasi generator angka acak
	  shell();
	}
	```
