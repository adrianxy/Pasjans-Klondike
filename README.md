# Pasjans Klondike - semestr 2 - projekt 2

Pasjans jest grą karcianą, której celem jest pozbycie się wszystkich kart zakrytych oraz tych znajdujących się na dolnym panelu

Zasady gry:
- Gracz układa karty malejąco na dolnej planszy, z czego karty muszą mieć naprzemienne kolory (czarny, czerwony)
- Gracz może przekładać dowolną ilość kart w kolumnie, o ile każda z kart niżej spełnia powyższą zasadę
- Na górze planszy Gracz układa karty o tej samej figurze rosnąco
- Gracz może użyć wierzchnią kartę z kupki w swoich akcjach
- Król ma największą wartość, a As najmniejszą
- t - trefl, p - pik, s - serce, k - kier

Opis działania programu:
- Program obsługuje tylko małe litery i cyfry
- Gracz może wykonać następujące ruchy:
  - Połuż kartę na początek kolumny - Gracz kładzie dowolną widoczną kartę i każdą pod nią na wolną kolumnę w dolnym panelu 
  - Dobierz kartę - Gracz kładzie wierzchnią kartę z kupki na spód kupki i odsłania nową wierzchnią kartę
  - Przenieś kartę na górną kupkę - Gracz kładzie na górny panel wybraną kartę (w jednej kolumnie ta sama figura, a kolejność rosnąca) 
  - Przenieś karty na inną kolumnę - Gracz przekłada daną kartę i każdą pod nią na określoną inną kartę 
  - Wartość i Kolor oddzielamy spacją, podajemy tylko małe litery i cyfry
