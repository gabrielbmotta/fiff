## Simple tools for reading fiff files in plain c++.

So far we've got the following:

### printfiff -
Prints the contents of a fiff file in non-binary form.
![printfiff](resources/images/printfiff.png)

### qfiff -
Quick lookup of tags, data types and block ids.
![printfiff](resources/images/qfiff.png)

### anonymizer
![anonymizer](resources/images/anonymizer.png)
Gets rid of PHI from fiff files. A feature-stripped reimplementation of [MNE Anonymize](https://github.com/mne-tools/mne-cpp).
