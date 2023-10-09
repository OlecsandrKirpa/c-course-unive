# Corso di C all'università Ca' Foscari di Venezia
Questa repository verrà utilizzata per pubblicare e versionare gli argomenti trattati nel corso.

## Sviluppo
Per rendere lo sviluppo più comodo è possibile avvalersi di uno script che ascolta le modifiche dei file .c ed esegue tali file quando cambiano.

Per fare ciò, si utilizza uno scriptino Ruby che richiede alcune librerie. Si esegua:
1. `bundle install`
2. `ruby listen.rb`


Ora Quando si modifica un qualsiasi file .c, questo verrà compilato. L'eseguibile verrà eseguito e subito dopo eliminato, lasciando la directory pulita.
