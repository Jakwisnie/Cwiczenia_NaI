workspace {
 
    model {
        user = person "User"
         software = softwareSystem "Przegladarka" {
       przeg = container "przegladarka"{
          user -> this "wpisanie w wyszukiwarke poszukiwanego produktu /frazy"
           this -> user "wyswietlenie listy produktow zwiazanych z zadana fraza"
           }
         
        }
         softwareSystem = softwareSystem "Allegro" {
         
        
         baza = container "baza produktow"{
           przeg -> this "wyszukiwanie zadanej frazy"
           this -> przeg "przekazanie wynikow"
            
             
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