# Overview
This project builds a binary `togreek` which converts ASCII shorthand to Ancient Greek unicode with diacriticals

For instance:

```
'aret/e → ἀρετή
```

Multiple diacritical marks can be combined.

For instance:
```
\`_a → ᾃ
```

The ordering of the modifiers does not matter. For instance, all of the following will produce the same letter:
```
\`_a → ᾃ

`\_a → ᾃ

_`\a → ᾃ
```

# Usage

**`illiad.txt`**
```
m^hnin /'aeide je\a Phlhi/adew 'Acil^ho>s
```
```
$ cat illiad.txt | togreek
μῆνιν ἄειδε θεὰ Πηληιάδεω Ἀχιλῆος
```

# Modifiers

| Modifier Name           | ASCII Symbol | Example      |
|-------------------------|--------------|--------------|
| Acute Accent            | /            | /a &rarr; ά  |
| Grave Accent            | \\           | \\a &rarr; ὰ |
| Circumflex Accent       | ^            | ^y &rarr; ῦ  |
| Rough Breathing Mark    | `            | `e &rarr; ἑ  |
| Smooth Breathing Mark   | '            | 'o &rarr; ὀ  |
| Iota Subscript/Adscript | \_           | \_A &rarr; ᾼ |
| Word-Final Sigma        | >            | >s &rarr; ς  |
| Macron                  | ~            | ~y &rarr; ῡ  |

# Letters
| ASCII | Greek |
|-------|-------|
| a     | α     | 
| b     | β     |
| c     | χ     |
| d     | δ     |
| e     | ε     |
| f     | φ     |
| g     | γ     |
| h     | η     |
| i     | ι     |
| j     | θ     |
| k     | κ     |
| l     | λ     |
| m     | μ     |
| n     | ν     |
| o     | ο     |
| p     | π     |
| r     | ρ     |
| s     | σ     |
| t     | τ     |
| u     | u     |
| v     | ψ     |
| w     | ω     |
| x     | ξ     |
| y     | υ     |
| z     | ζ     |
