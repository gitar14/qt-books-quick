CREATE TABLE Kategori(
   kd_kategori INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   nama_kategori VARCHAR(25) NOT NULL
);

CREATE TABLE Penerbit(
   kd_penerbit INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   nama_penerbit VARCHAR(25) NOT NULL,
   alamat_penerbit VARCHAR(30) NOT NULL
);

        
CREATE TABLE Buku(
   kd_buku INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   kd_kategori INTEGER NOT NULL,
   kd_penerbit INTEGER NOT NULL,
   judul VARCHAR(25) NOT NULL,
   jumlah_hilang INTEGER NOT NULL,
   penulis VARCHAR(25) NOT NULL,
   tahun_terbit INTEGER NOT NULL,
   FOREIGN KEY (kd_kategori)
       REFERENCES Kategori(kd_kategori),
   FOREIGN KEY (kd_penerbit)
       REFERENCES Penerbit(kd_penerbit)
);

CREATE TABLE User(
   id_user VARCHAR(15) NOT NULL PRIMARY KEY,
   nama_depan_user VARCHAR(25) NOT NULL,
   nama_belakang_user VARCHAR(25) NOT NULL,
   role ENUM('Admin', 'Pegawai') NOT NULL,
   password VARCHAR(100) NOT NULL
);

CREATE TABLE Detail_Pengadaan(
   kd_detail_pengadaan INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   id_user VARCHAR(15) NOT NULL,
   sumber VARCHAR(25) NOT NULL,
   tanggal_pengadaan DATE NOT NULL,
   FOREIGN KEY (id_user)
      REFERENCES User(id_user) 
);

CREATE TABLE Pengadaan(
   kd_pengadaan INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   kd_detail_pengadaan INTEGER NOT NULL,
   kd_buku INTEGER NOT NULL,
   jumlah_pengadaan_buku INT NOT NULL,
   FOREIGN KEY (kd_buku)
       REFERENCES Buku(kd_buku),
   FOREIGN KEY (kd_detail_pengadaan)
       REFERENCES Detail_Pengadaan(kd_detail_pengadaan)
);


CREATE TABLE Member(
   kd_member INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   tanggal_lahir_member DATE NOT NULL,
   nama_depan_member VARCHAR(25) NOT NULL,
   nama_belakang_member VARCHAR(25) NOT NULL
);

CREATE TABLE Detail_Peminjaman(
   kd_detail_peminjaman INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   id_user VARCHAR(15) NOT NULL,
   kd_member INTEGER NOT NULL,
   tanggal_peminjaman DATE NOT NULL,
   lama_peminjaman INTEGER NOT NULL,
   tanggal_pengembalian DATE,
   FOREIGN KEY (id_user)
       REFERENCES User(id_user),
   FOREIGN KEY (kd_member)
       REFERENCES Member(kd_member)
);

CREATE TABLE Peminjaman(
   kd_peminjaman INTEGER NOT NULL PRIMARY KEY AUTO_INCREMENT,
   kd_detail_peminjaman INTEGER NOT NULL,
   kd_buku INTEGER NOT NULL,
   denda INTEGER NOT NULL,
   FOREIGN KEY (kd_detail_peminjaman)
       REFERENCES Detail_Peminjaman(kd_detail_peminjaman),
   FOREIGN KEY (kd_buku)
       REFERENCES Buku(kd_buku)
);
