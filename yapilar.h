//
//  yapilar_h
//  yapilar
//
//  Created by cagatay on 30.12.2015.
//  Copyright © 2015 cagatay. All rights reserved.
//

#ifndef yapilar_h
#define yapilar_h

/* Projemizde kullanacağımız struct'ları içeren başlık dosyamız */
struct istatistikler
	{
		int id;
		int gol_sayisi;  /* Gol sayısını burada tutacağız. */
		int mac_sayisi; /* Mac sayısını burada tutacağız. */
		int oyuncu_sayisi; /* Oyuncu sayısını burada tutacağız. */
		int takim_sayisi; /* Takım sayısını burada tutacağız. */

		struct gol_krallari /* Gol kralı olan oyuncuları burada tutacağız. */
		{
			int id;
			struct oyuncular *oyuncu; /* Oyuncu nesnesiyle ilişkili */

		}gol_krali[100];

		struct oyuncular *kendi_kalesine_en_cok_atan_oyuncu;

		struct hattricks /* Gol kralı olan oyuncuları burada tutacağız. */
		{
			int id;
			struct oyuncular *oyuncu; /* Oyuncu nesnesiyle ilişkili */
			struct maclar *mac; /* Oyuncu nesnesiyle ilişkili */

		}hattrick[100];

		int hattrick_sayisi;
		int gol_krali_sayisi;
		
		int birinci_devrede_atilan_gol_sayisi;
		int ikinci_devrede_atilan_gol_sayisi;

	}istatistik;

struct oyuncular
		{
			int id;
			char oyuncu_on_ad[100];
			char oyuncu_son_ad[100];

			int gol_sayisi;
			int kendi_kalesine_gol_sayisi;

			struct takimlar *takim;

		}oyuncu[100];

struct takimlar
	{
		int id;
		char takim_on_ad[100];
		char takim_son_ad[100];

		int oynadigi_mac_sayisi;
		int atilan_gol_sayisi;
		int yenilen_gol_sayisi;
		int galibiyet_sayisi;
		int malubiyet_sayisi;
		int beraberlik_sayisi;
		int puan;
	

	}takim[50];

struct goller
	{
		int id;
		int dakika;
		struct takimlar *takim; /* Golu atan takım. */
		struct oyuncular *oyuncu; /* Oyuncu nesnesiyle ilişkili */
		struct maclar *mac;
		//int kendi_kalesine;

	}gol[100];

struct maclar
	{
		int id;
		
		struct takimlar *ev_sahibi;
		struct takimlar *misafir;
		int ev_sahibi_gol_sayisi;
		int misafir_gol_sayisi;

	}mac[150];

#endif /* yapilar_h */
