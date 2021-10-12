workspace {
 
    model {
        user = person "User"
        
         softwareSystem = softwareSystem "Allegro" {
         
         konto = container "system zarzadzania kontami"{
           user -> this "rejestracja e-mail wraz z akceptacja regulaminu" "2fa"
           
         }
         baza = container "baza danych uzytkownikow"{
         
         konto -> this "wprowadzenie uzytkownika do bazy"
         
        }
        }
        faceboook = softwareSystem "Facebook" {
        
          facebook = container "facebook" {
                user -> this "logowanie facebook""OAuth 2.0"
                this -> konto "przekazanie danych"
        }
        }
        gooogle = softwareSystem "Google" {
        
         google = container "google" {
                user -> this "logowanie google""OAuth 2.0"
                this -> konto "przekazanie danych"
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