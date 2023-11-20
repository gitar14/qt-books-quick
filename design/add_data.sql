INSERT INTO Kategori 
(kd_kategori, nama_kategori)
VALUES
(1,'Pemrograman'),
(2,'Basis Data'),
(3,'Matematika'),
(4,'Kewarganegaraan'),
(5,'Pemasaran'),
(6,'Pengembangan Diri');

INSERT INTO Penerbit 
(kd_penerbit, nama_penerbit, alamat_penerbit)
VALUES
(1,'Informatika','Bandung'),
(2,'Andi Publisher','Yogyakarta'),
(3,'Erlangga','Jakarta'),
(4,'Graha Pustaka','Surakarta'),
(5,'Bumi Merdeka','Jakarta'),
(6,'Lokomedia','Yogyakarta'),
(7,'Gramedia Pustaka Utama','Jakarta');

INSERT INTO Buku
(kd_buku, kd_kategori, kd_penerbit, judul, jumlah_hilang, penulis, tahun_terbit)
VALUES
(1,1,1,'Teori Aplikasi C++',0,'R.H. Sianipar',2017),
(2,1,1,'Delphi Accounting',0,'G.H. Away',2011),
(3,1,1,'Delphi Firebird',0,'G.H. Away',2008),
(4,1,2,'Pemrograman JavaScript',0,'Abdul Kadir',2009),
(5,1,2,'Pemrograman Berbasis Obyek',0,'Abdul Kadir',2008),
(6,3,1,'Matematika Distkrit',0,'Rinaldi Munir',2020),
(7,3,3,'Kalkulus',0,'Purcell',2010),
(8,6,7,'Atomic Habit',0,'James Clear',2019),
(9,2,2,'Belajar MySQL',0,'Abdul Kadir',2008);


INSERT INTO 
User 
(id_user, nama_depan_user, nama_belakang_user, role, password)
VALUES
('admin','Levi','Rizki Saputra','Admin','levu'),
('jepe','Narindira','P','Pegawai','jep'),
('dida','Dida','Attala','Pegawai','did'),
('van','Revano','T','Pegawai','van'),
('gita','Gita','Ristya','Pegawai','git');

INSERT INTO 
Detail_Pengadaan 
(kd_detail_pengadaan, id_user, sumber, tanggal_pengadaan)
VALUES
(1,'jepe','Pembelian di Gramedia', '2023-09-01'),
(2,'dida','Pembelian di Andi', '2023-09-02'),
(3,'van','Pembalian di Bi-Obses', '2023-09-03');

INSERT INTO Pengadaan 
(kd_buku, kd_detail_pengadaan, jumlah_pengadaan_buku)
VALUES
(8,1,5),
(7,1,2),
(1,2,1),
(4,2,2),
(5,2,3),
(9,2,2),
(2,3,1),
(3,3,1),
(6,3,3);

INSERT INTO Member 
(kd_member, nama_depan_member, nama_belakang_member, tanggal_lahir_member)
VALUES
(1,'Faiz','al-Ghifari','2021-10-13'),
(2,'Faiz','Rigel','2023-11-20'),
(3,'Tegar','Bramastyo','2023-11-20'),
(4,'Azril','Fahmiyati','2023-11-20'),
(5,'Isyraf','Fajar','2023-11-20'),
(6,'Kadek','Garry','2023-11-20');

INSERT INTO
Detail_Peminjaman 
(kd_detail_peminjaman, kd_member, id_user, tanggal_peminjaman, lama_peminjaman, tanggal_pengembalian)
VALUES
(1,2,'jepe','2023-11-01',7,'2023-11-09'),
(2,1,'dida','2023-11-02',10, '2023-11-10'),
(3,4,'van','2023-11-05',5,'2023-11-10'),
(4,5,'gita','2023-11-15',10, NULL),
(5,3,'gita','2023-11-19',10, NULL);

INSERT INTO Peminjaman
(kd_buku, kd_detail_peminjaman, denda)
VALUES
(6,1,1000),
(7,1,1000),
(8,2,NULL),
(9,2,NULL),
(1,3,NULL),
(5,3,NULL),
(2,4,NULL),
(3,4,NULL),
(4,5,NULL);
