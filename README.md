# Tugla-Kirma-Oyunu
Oyunumuz bir tuğla kırma oyunudur. Potansiyometre ile  hareket ettirilen bir palet bulunmaktadır. Sürekli hareket halinde olan topun ekranın aşağısına düşmesini engelleyerek palet  üzerine düşmesini sağlamaya çalışılmaktadır.

 Ekranın di ˘ ger ˘kısımları ; sag , sol ve yukarı : duvar olarak kabul edilmektedir ˘
ve yop bu kısımlara geldginde çarparak oyun hareketine devam ˘
eder .Bütün tuglalar kırıldı ˘ gıdında yeni levele geçildi ˘ gine dair ˘
bilgilendirme mesajı gelir ve tugla boyutları ve aralıkları daha ˘
küçülmü¸s olarak yeni bir ekran gelir bu ¸sekilde her sefefrinde
dahah zor bir levele geçilmi¸s olur. Oyun ba¸sında ise oyuncuya
3 can verilir top 3 kez a¸sagıya dü¸stü ˘ günde oyun sonlanır. Oyun ˘
sonunda skoru ve oyunun bittigine dair bilgilendirme mesajı ˘
ekarana gelir, belirli bir süre sonra kaybolur ve menü kısmı
açılır artık oyun yeni bir oyun için hazır hale getirilir.


II. G˙IR˙I ¸S
Oyunumuz wokwi uygulamasında tasarlanıp yine bu uygulama üzerinde yazılmı¸stır. Arduino seçimi olarak UNO ARDUINO seçilmi¸stir. Oyun sırasında skor takibi yapılması için
4 digit display kullanılmı¸stır. Oyun ekranı için OLED ekran
kullanılmı¸stır. Oyun sırasında kullanıcının hareket ettirmesi
gereken paleti potasiyometre ile kontrol edilmektedir.Aynı ¸sekilde menü de ilerlemek içinde potansiyometre kullanılmı¸stır.
Seçme i¸slemleri içinse bir adet buton kullanılmı¸stır. Her oyun
ba¸sladıgında oyuncunun 3 adet canı olması gerekti ˘ ginden ve ˘
can takibi yapmak için 3 adet canların göstergesi led kullanılmı¸stır.Oyun kodlarının optime olarak yazılmasına dikkat
edilmi¸stir. Oyun akıcı bir ¸sekilde oynanabilmektedir.


III. YÖNTEM
Oyunumuz ba¸slangıç olarak bir menü ile bizi kar¸sılıyor.
Menü de iki seçenek bulunuyor : ba¸slat ve çıkı¸s. Seçenekler
arasında ilerlemek için potansiyormte kullanıldı. Potansiyometre degerinin ne oldu ˘ guna göre ekranda seçim gösteriliyor. ˘
Seçilmek istenen seçenege gelindi ˘ gindinde seçim botunu ile ˘
seçiliyor.Ba¸slat seçildiginde tu ˘ gla kırma oyunumuz ba¸slatıl- ˘
maktadır .Oyunun topu oyun ba¸sında ekranı ortasında ba¸slayıp
yukarı dogru kareket etmeye ba¸slar hareket etmesi birer birim- ˘
lik kareketlerlerle olu¸stutulmu¸stur. loop içinde çagırıldı ˘ gından ˘
dolayı süreklilik halinde bir hareketlilik söz konusu olur. Oyun
ekranın sag , sol ve yukarı kısımları duvar kabul edilip bu ˘
kısımlara top geldiginde hareket yönü terse çevirilerek farklı ˘
bir yöne gitmesi saglanmaktadır. A¸sa ˘ gı yöne do ˘ gru bir yer ˘
çekimi varsayılmakadır.Top a¸sagı kısıma geldi ˘ ginde yanmı¸s ˘
olur. Yanmamak için topun palet üzerine gelmesi gerekir. Oyun
palet hareket ettirilerek oynananır. Palet ise potansiyometre
ile harket ettirilmektedir.Oyun içerisinde 3 can bulunmaktadır.
Bu canlar ledler ile gösterilmektedir. 3 Can da tükendiginde ˘
oyunun bittigine dair ekranda bir mesaj gelir . Bu mesajda skor ˘
bilgisi de yer alır. Ekrandaki bütün tuglalar canlar tükenmeden ˘
kırıldıgında tu ˘ gla boyutları ve tu ˘ glallar arasındaki boyutlar bir ˘
öncekine göre daha küçük olacak ¸sekilde yeni levele geçilir.
Yeni level de topun hızı da artmı¸s olur. Bu ¸sekilde her yeni
seviyede oyun biraz daha zorla¸stırılmı¸s olur . Her on tuglada ek ˘
bir can dü¸ser eger kullanıcı paletin üzerine bu canı dü¸sürmeyi ˘
ba¸sarabilirse can bir tane daha artar . Senkronize bir ¸sekilde
ledler de can sayısına göre yanar . Oyun skoru seven segment
ile gösteriliyor . Skor takibi bu ¸sekilde yapılabilir.

A. FONKS˙IYONLAR
Oyunun akıcı olması için çe¸sitli fonksiyonlar kullanılmı¸stır.
Tuglaları , paleti ve topu çizmek için drawGame fonksiyonu ˘
bulunmaktadır.Renk degi¸stirme butonunda seçilen renge göre ˘
top palet ve tuglalar çizilmektedir.Loop kısımda ek can kont- ˘
rolü saglandı ˘ gında e ˘ ger can verilmesi gerekiyor ise heratArtive ˘
true olarak atanır ve can da ekrana çizdilir. Her yeni seviyeye geçildiginde bazı de ˘ gi¸skenler güncellenmesi gerekir. Bu ˘
degi¸skenleri güncelledi ˘ gimiz fonksiyon advanceToNextLevel . ˘
Burada tugla boyutları küçültülür , top hızı arttırılır , tu ˘ glalar ˘
arasındaki bo¸sluklar arttırılır. Aynı zamanda EKran temizlenir
ve yeni sevieyey geçildigine dair ekrana bilgilendirme mesajı ˘
yazdırılır. Menü için ayrı bir fonksiyon kullanılır. 2 Adet seçim
seçenegi bulnur potansiyometrenin konumuna göre hsngi se- ˘
çenegin seçildi ˘ gini belirli eden bir i¸saret ekrana yazdırılan bir ˘
fonksiyondur. Menü seçeneginde seçilen seçenekler için fonk- ˘
siyonlar bulunur . BUnlar : startGame ve exitGame . startGame
fonksiyonu öncelikle oyunun ba¸slayıp ba¸slamamasını kontrol
eden degi¸skeni true yapar . daha sonra pyun ba¸slangıçında can ˘
adetinin 3 olması gerektiginde can adetinin 3 oldu ˘ gundan emin ˘
olur . Diger levele geçildi ˘ ginde oyun ayarları de ˘ gi¸stirildi ˘ ginden ˘
bu kısımda hepsini eski ayarına getirmek istenilir. Bunun için
gerekli atamalar yapılır. exitGame fonksiyonunda ise oyun
ba¸slamasını kontrol eden degi¸skeni gameRunning false ola- ˘
rak atama yapılır ve bu ¸sekilde oyunun ba¸slaması engellenir
.Ekrana oyunun durdurulduguna dair bir bilgilendirme mesajı ˘
yazdılır.


IV. DENEYSEL SONUÇLAR
Oyunun akıcı olması için gerekli optimizasyon kurallarına
uyum saglanması gerekti ˘ gi ö ˘ grenildi. Oyun sırasında Loop ˘
kullanımı daha iyi kullanılmaya çalı¸sıldı . Bir birimlik hareket
etme ekranan bunu yansıtmanın dahah kolay oldugu ö ˘ grenilmi¸s ˘
olundu. Arduino seçiminde yapılacak i¸sin detayları ara¸stırılıp
hangi arduino seçiminin dahha iyi olacagı denendi ve en ˘
mantıklsının uno olduguna karar verildi. Her kısım için ayrı ˘
ayrı malzeme degilde tekrar tanımla ile bir malzemeyi iki ˘
kez kullanarak daha verimli bir çalı¸sma elde edinebilecegi˘
ögrenildi. ˘


V. SONUÇ
Arduino Uno üzerinde potansiyometre ile kontrol edilebilen bir tugla kırma oyunu tasarlandı . Oyun içerisinde canları ˘
gösteren ledler ,ekstra can gönderme , seven segment de e¸s
zamanlı olarak skoru yazdırma , bir menü ile kullanıcının
yapmak istedigi i¸slemi seçme i¸slemleri yapıldı. Oyun içerisinde ˘
belili bir süreklilik olu¸sturuldu .Oyuncunun 3 adet canı bitmeden oyunun tükenmeden yeni leveller olu¸sturulması saglandı
