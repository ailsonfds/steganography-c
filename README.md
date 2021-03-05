# Steganography in C

This is a project from 2017

## Method description abstract

Steganography is the art of conceal something on things, like a message in a painting or a painting in a message (why not?). This work consists on hiding messages in pictures (BITMAP format or PPM format) or reading hidden messages inside them.

To achieve this goal we use a tecnique that consists in change the least significant bit on each byte of the image so the original picture does not be very different from the modified version and people don't spot the difference without look at it.

## Running

### Conceal message

```bash
bin/steg -i <input_message_file> -f [ 'bmp' | 'ppm' ] <image_file_path> -e
```

### Reveal message

```bash
bin/steg -o <output_message_file> -f [ 'bmp' | 'ppm' ] <image_file_path> -d
```

