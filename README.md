# SimpleProceduralPuzzleGame
simple puzzle game automatically generated from custom input  - c++ introduction course project (sfml)

## Koncept
Jest to szkielet to generowanie bardzo, bardzo podstawowej układanki logicznej w postaci układania obrazka przez przesuwanie kafelek - uzytkownik decyduje ile jest możliwych etapów, ich grafikę oraz poziom trudności. Gra generuje proceduralnie poziomy i menu na podstawie wprowadzonych danych, dzięki czemu dodawanie kolejnych etapów jest banalnie proste oraz jedynym dodatkowym plikiem do przechowywania w folderze gry jest pojedyncza grafika. Program jest funkcjonalny, ale bardzo podstawowy - bardziej w fazie proof of concept.

## Zawartość

### GUI
Program składa się z automatycznie generowanego menu - będzie się powiększać w miarę zwiększania ilości poziomów - oraz samych poziomów. Możliwe jest wyjście z poziomu z powrotem do menu, przy czym postęp użytkownika zostanie w takim wypadku zapisany. Nie istnieje jednak możliwość zapisu i wczytania gry po zamknięciu. Każdy poziom składa się z układanki oraz podglądu ułożonego obrazka, dostępnego przytrzymaniem prawego przycisku myszki.

Ze względu na ograniczenia czasowe oraz znikomą trudność programistyczną oprawa graficzna interfejsu użytkownika jest taka jaka jest, czyli jej nie ma. Jednakże minimalizm ma również swój urok, prawda?

### Programowanie poziomów
Dane o poziomach przekazywane są do ciała gry w postaci wektora specjalnych krotek zawierających pole z nazwą/ścieżką do pliku z obrazem oraz wielkością pojedynczych kafelek. Aby program działał poprawnie obrazek powinien być wielkości 800x800 pixeli (jednak inna wielkość nie powinna spowodować nieprawidłowego działania programu, jedynie zakłucenia wizualne), a wielkość kafelek powinna być dzielnikiem liczby 800 (inna wartość może zepsuć działanie poziomu). Długość listy jest dowolna.

### Użyte środowisko
Do zbudowania silnika gry posłużyła biblioteka C++ SFML ze względu zarówno na prostotę i wystarczającą ilość opcji, jak również fakt że do niedawna była w miarę powszechnym sposobem budowania silników gier w C++.

### Żródła grafiki
Wszystkie grafiki użyte do stworzenia gry zostały zaczerpnięte ze strony royalty free stock photos pexels.com, gdzie zostały udostępnione z licencją free to use.

### Dodatkowa zawartość która mogłaby być zaimplementowana w pełnej wersji (aka gdyby nie było sesji)
- muzyka: SFML oferuje obsługę dźwięku, jednak nie został on włączony do gry głównie ze względu na mniejsze zasoby free to use oraz bycie dodatkiem czysto estetycznym
- tworzenie własnych poziomów: user input w sfml-u jest nieco bardziej skomplikowany :/ Uznałam że input konsolowy niewiele się różni od tego w kodzie.
- wygranie gry: głównie ze względu na optymalizację ta wersja gry nie przewiduje naklejki 'dobra robota' za ułożenie gry
- timer: żeby gracz mógł wiedzieć na ile odcinków Friends mógłby w tym czasie zmarnować czas
- best scores: dla nerdów

