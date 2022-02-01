# lox

Lox (funky transliteration of LOCs) is a terminal code editor for myself, born out of a  
"if I had dime ..." moment. As in, if I had written a chunk of code for every time I complained  
about never finding the ideal code editor, by now I might have one of my own. If code is a craft  
and decent craftsmen make their own tools, it makes sense to roll out your own code editor.

So, more doing and less complaining.  

And by the way, of all code editors, I like Vim's concept best but am dissapointed by how it has    
evolved, the quality of its code and the state of the plugin ecosystem.  

Isn't it ironic that after so many decades, we developers have built outstanding software of all  
kinds but have failed to deliver the code editor we all deserve?

## Design

Code editors are the kind of application that tends to be attracted to high coupling and to avoid  
this, often you need a conscious effort to stay clear of the path of less resistance. That is, from  
the solutions that seem easy and straightforward at first and later turn into rabbitholes.

As an an example, consider text edition data structures. They only need two operations, insert and   
delete. Typical text operations like navigation, search, etc. should be defined outside of the container  
structure. At first sight, this seems to increase the implementation level of complexity, even with worst  
performance. After some thinking, the possibility of creating a monolythic text container starts to be  
tempting. And voila, there you go down the rabbithole.

Of course, you can get away with building a great super monolythic editor, Vim is a perfect example.  
But this is a long term project for myself and hopefully it will yield an editor I can use and extend in the  
years to come. Modularity and maintenability come first, even if I have to sacrifice a bit of performance.

It has zero dependencies (no ncurses) but I expect at some point I will need to integrate external libs for  
the language heavy lifting parts e.g. LSP support.

This project was actually started in Rust, you can check it out [here](https://github.com/eddieshan/foo-editor). Some time after, however, it dawned   
on me that integration with external libs would be a pain, given Rust's poor FFI story. I am cool with bindgen  
or writing wrappers in other contexts, just not here as this is a project where I want minimum friction.