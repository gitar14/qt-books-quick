CREATE TABLE IF NOT EXISTS Kategori(
   kd_kategori VARCHAR(4) NOT NULL PRIMARY KEY,
   nama_kategori VARCHAR(25) NOT NULL
);

CREATE TABLE IF NOT EXISTS Penerbit(
   kd_penerbit VARCHAR (4) NOT NULL PRIMARY KEY,
   nama_penerbit VARCHAR(25) NOT NULL,
   alamat_penerbit VARCHAR(30) NOT NULL
);

        
CREATE TABLE IF NOT EXISTS Buku(
   kd_buku VARCHAR(4) NOT NULL PRIMARY KEY,
   kd_kategori VARCHAR(4) NOT NULL,
   kd_penerbit VARCHAR(4) NOT NULL,
   judul VARCHAR(25) NOT NULL,
   jumlah_hilang INTEGER NOT NULL,
   penulis VARCHAR(25) NOT NULL,
   tahun_terbit INTEGER NOT NULL,
   FOREIGN KEY (kd_kategori)
       REFERENCES Kategori(kd_kategori),
   FOREIGN KEY (kd_penerbit)
       REFERENCES Penerbit(kd_penerbit)
);

CREATE TABLE IF NOT EXISTS User(
   id_user VARCHAR(15) NOT NULL PRIMARY KEY,
   nama_depan_user VARCHAR(25) NOT NULL,
   nama_belakang_user VARCHAR(25) NOT NULL,
   role ENUM('Admin', 'Pegawai') NOT NULL,
   password VARCHAR(100) NOT NULL
);

CREATE TABLE IF NOT EXISTS Sumber_Pengadaan(
   kd_sumber_pengadaan VARCHAR(4) NOT NULL PRIMARY KEY,
   id_user VARCHAR(15) NOT NULL,
   nama_sumber VARCHAR(25) NOT NULL,
   FOREIGN KEY (id_user)
      REFERENCES User(id_user) 
);

CREATE TABLE IF NOT EXISTS Pengadaan(
   kd_pengadaan VARCHAR(4) NOT NULL PRIMARY KEY,
   kd_sumber_pengadaan VARCHAR(4) NOT NULL,
   kd_buku VARCHAR(4) NOT NULL,
   jumlah_pengadaan_buku INT NOT NULL,
   FOREIGN KEY (kd_buku)
       REFERENCES Buku(kd_buku),
   FOREIGN KEY (kd_sumber_pengadaan)
       REFERENCES Sumber_Pengadaan(kd_sumber_pengadaan)
);


CREATE TABLE IF NOT EXISTS Member(
   kd_member VARCHAR (4) NOT NULL PRIMARY KEY,
   tanggal_lahir_member DATE NOT NULL
   nama_depan_member VARCHAR(25) NOT NULL,
   nama_belakang_member VARCHAR(25) NOT NULL,
)

CREATE TABLE IF NOT EXISTS Detail_Peminjaman(
   kd_detail_peminjaman VARCHAR(4) NOT NULL PRIMARY KEY,
   id_user VARCHAR(4) NOT NULL,
   kd_member VARCHAR(4) NOT NULL,
   tanggal_peminjaman DATE NOT NULL,
   lama_peminjaman INTEGER NOT NULL,
   tanggal_pengembalian DATE,
   FOREIGN KEY (id_user)
       REFERENCES User(id_user)
   FOREIGN KEY (kd_member)
       REFERENCES Member(kd_member),
);

CREATE TABLE IF NOT EXISTS Peminjaman(
   kd_peminjaman VARCHAR(4) NOT NULL PRIMARY KEY,
   kd_detail_peminjaman VARCHAR(4) NOT NULL
   kd_buku VARCHAR(4) NOT NULL,
   denda INTEGER NOT NULL,
   FOREIGN KEY (kd_detail_peminjaman)
       REFERENCES Peminjaman_Detail(kd_peminjaman_detail)
   FOREIGN KEY (kd_buku)
       REFERENCES Buku(kd_buku),
);