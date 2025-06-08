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
5. Mendefinisikan makro `INT_KBD` yang merepresentasikan layanan interupsi keyboard untuk BIOS dengan integer `0x16` atau `16h` di mana dalam penerapannya digunakan untuk melakukan proses interaksi dengan keyboard seperti membaca keypress menggunakan function `interrupt()`.

```c
#define TELETYPE    0X0E
```
6. Mendefinisikan makro `TELETYPE` dengan value `0x0E` yang merepresentasikan suatu subfungsi dari integer `0x10` atau `10h` di mana dalam penerapannya digunakan untuk menampilkan satu karakter ASCII ke layar dengan keluaran teletype (mesin ketik) dan setelahnya akan menggeser kursor ke kanan sebanyak satu karakter ASCII menggunakan function `interrupt()` dan melalui register `AH`.
  
	Namun, pada program `EorzeOS` subfungsi `TELETYPE` tidak digunakan karena pada proses penampilan karakter ASCII ke layar tidak menggunakan function `interrupt()`, melainkan menggunakan pendekatan manual dengan proses perhitungan offset pada layar ntuk menentukan letak di mana karakter ASCII akan diletakkan yang 		implementasinya diterapkan pada function `putc()` yang pada dasarnya dapat dilakukan dengan bantuan function `putInMemory()`.

```c
#define KEYBOARD    0X00
```
7. Mendefinisikan makro `KEYBOARD` dengan value `0x00` yang merepresentasikan suatu subfungsi dari integer `0x16` atau `16h` di mana dalam penerapannya digunakan untuk menunggu keypress dari keyboard dan akan membaca satu karakter ASCII menggunakan function `interrupt()` dan melalui register `AL`.

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
15. Mendefinisikan makro `BUFFER` yang merepresentasikan suatu konstanta di mana dalam penerapannya digunakan untuk mendefinisikan batas maksimum area memori yang digunakan untuk penampungan sementara karakter input yang dimasukkan melalui function `readString()` yang di mana pada kasus program `EorzeOS` besarnya adalah `127` karakter ditambah dengan satu `\0`.

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
35. Apabila suatu karakter ASCII yang hendak diletakkan pada layar merupakan karakter dengan nilai ASCII `0` yang merujuk pada karakter `\0`, maka function `putc()` tidak akan meletakkan apapun pada layar dan proses function `putc()` tidak akan dilanjutkan dan akan kembali ke tempat di mana function `putc()` dipanggil.

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

#### • Print String
#### • Read String
#### • Clear Screen

### • Stdlib

### • Shell

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

### • Revisi
