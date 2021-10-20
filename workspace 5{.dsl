workspace {
 
    model {
        user = person "User"
         software = softwareSystem "Przegladarka" {
       przeg = container "przegladarka"{
          user -> this "wpisanie w wyszukiwarke poszukiwanego produktu /frazy"
           this -> user "wyswietlenie listy produktow zwiazanych z zadana fraza"
            user -> this "wcisniecie na ikone produktu"
           this -> user "wyswietlenie informacji o produkcie"
            }
         
        }
         softwareSystem = softwareSystem "Allegro" {
         
        
         baza = container "baza produktow"{
           przeg -> this "wyszukiwanie zadanej frazy"
           this -> przeg "przekazanie wynikow ze zwiazana fraza "
           przeg -> this "wyszukanie id produktu"
           this -> przeg "podanie informacji o produkcie"
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