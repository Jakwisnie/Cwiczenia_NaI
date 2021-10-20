workspace {
 
    model {
        user = person "User"
         software = softwareSystem "Przegladarka" {
       przeg = container "przegladarka"{
          user -> this "wpisanie w wyszukiwarke poszukiwanego produktu /frazy"
           this -> user "wyswietlenie listy produktow zwiazanych z zadana fraza"
            user -> this "wcisniecie na ikone produktu"
           this -> user "wyswietlenie informacji o produkcie"
            user -> this "wcisniecie na nazwe sprzedawcy"
           this -> user "wyswietlenie informacji o sprzedawcy w panelu bocznym"
           }
         
        }
         softwareSystem = softwareSystem "Allegro" {
         
        
         baza = container "baza produktow"{
           przeg -> this "wyszukiwanie zadanej frazy"
           this -> przeg "przekazanie wynikow ze zwiazana fraza "
           przeg -> this "wyszukanie id produktu"
           this -> przeg "podanie informacji o produkcie"
            }
             
         baza2 = container "baza uzytkownikow"{
           przeg -> this "wyszukiwanie uzytkownika"
           this -> przeg "przekazanie adresu konta szukanego uzytkownika"
            
             
         }
         
         
        }
        
            
    }
 
    views {
        systemContext softwareSystem {
            include *
            autolayout lr
        }
 
        container softwareSystem {
            include *
            autolayout lr
        }
  systemlandscape softwareSystem {
               include *
            autolayout lr
        }
       
 
        theme default
    }
 
}