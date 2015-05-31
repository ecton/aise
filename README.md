# What is Aise?

Aise is a language and runtime whose goal is to simplify cross-platform development. While many cross-platform languages have come and gone, they all have their weaknesses and strengths. Aise will not be perfect, but it will be practical and will attempt at doing the best job possible at allowing code reuse and staying out of the way of you as a developer.

The word [aise](http://en.wiktionary.org/wiki/aise) is the [origin of "ease" in English](http://www.etymonline.com/index.php?term=ease&allowed_in_frame=0). Additionally, from the Wiktionary link, the current meanings all describe what Aise is trying to provide in a language for developers.

## Initial Goal of Aise

Aise's first major milestone is to provide a more feature-rich langauge than Lua that can be embedded as easily as Lua in C and Java. More specifically, it's initial targets are a Ruby gem, an iOS library, and an Android jar. However, beyond [character encodings](http://en.wikipedia.org/wiki/Character_encoding) there will be as little as possible in terms of platform specific API usage.

When this goal is achieved, you will be able to comiple your Aise source down to byte code, and execute that byte code on multiple platforms. You will also be able to extend the runtime with natively provided code.

## Long-term Goals of Aise

### Runtimes

The runtimes will be expanded to include a rich set of functionality from low-level features including file io and socket io to high-level features including a user interface layer and OpenGL layer.

### Builds

There will be a build tool that will be able to generate a stand-alone iOS or Android application, and perhaps other platforms as well.

### Platforms

Other platforms may also receive runtimes, such as a runtime written in C# that could target Windows Phone or Windos Desktops