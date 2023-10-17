*COPYRIGHT RUSU BOGDAN, 312CAa 2022-2023*

# Image Editor

* The code is organized in multiple .h's containing the definitions of functions
and structures and their coresponding .c's that contain the bodies of these
functions. The main .c is image_editor.c contain just the main while loop
and the operation that is read from the standard input. For the rest of the
reading we use the functions in ops_skeleton.h and ops_skeleton.c and call
different functions from the specific headers.


* The solution is comprised of a while loop in the main that ends iff the
signaled operation is 'EXIT', which deallocates all the used memory through
the free_img_rgb() or free_img_gs() functions, depending on the type of image
that is loaded.

* For every operation that is read a specific action is taken. If the entered
operation is not in the recognizable commands, an alert is printed that
an 'Invalid command' was entered.

* For the 'LOAD' operation, it is checked whether the file was opened
successfully or not (in the case it doesn't exist). Then we open the file in
binary mode to extract the format of the file. Depending on the format, one of
the functions contained in extract_info.h is called to extract the information
of the given file. In the case of an ascii file, it is checked whether the
current line is a comment and thus ignored with the ignore_comm() function.
The information is loaded into the respective structures for further use.
  * `usage example` : LOAD dummy.ppm

* For the 'SAVE' operation, first we read the input after the effective
command, splitting it into tokens. The valid number of parameters is 1 (binary)
or 2 (ascii). With respect to the type of file we want to save as, a
specific function is called and a file created with the content of the image.
  * `usage example`: SAVE dummy_output ASCII/ SAVE dummy_output

* For the 'SELECT' operation, we initialize 4 more parameters in the image
structure, x1, y1, x2, y2, meaning the current selection. Initially, those
fields are set to display the full image, aka SELECTED ALL. Similarly, we
read the input after the effective command and split it into tokens. We
have 2 permitted situations. If we have 1 parameter and that is 'ALL', we
select the whole image as we did initially. If the given input consists of
4 values we check whether the string tokens are containing digits or '-'
at the beginning of the string token. If we have valid string tokens we
convert them into integers and check whether the suppossed selection is a
valid one. If it is, we modify the parameters into the new selection. Contrary,
we keep the last valid selection.
  * `usage example`: SELECT ALL/ SELECT 0 0 100 100

* For the 'CROP' operation, we realloc the matrix of pixels of the current image
and copy the contents inside the current selection in an auxiliary matrix.
After the reallocation, we transfer the contents of the auxiliary matrix in the
pixel matrix member of the structure and set the selection parameters so as to
display the current image. After that, we free the auxiliary matrix.
  * `usage example`: CROP

* For the 'APPLY' operation we apply the same logic with token splitting as we
did with the 'SELECT' operation, checking if the one parameter on the same
line as the 'APPLY' string exists, is only 1 and is one of the valid strings
of effects. For each effect, we initialize a specific kernel or normalized
convolution matrix and we apply the algorithm given in the Wikipedia
documentation, overlaping the kernel's center on the current element, and if
the current element has sufficient neighbours, we multiply the overlapping
elements and transfer the sum of these products in the current element, in
an auxiliary matrix, of course. If the results are bigger than 255 or less
than 0, we implemented a clamp function that bounds them in interval.
  * `usage example`: APPLY SHARPEN/BLUR/GAUSSIAN_BLUR/EDGE

* For the 'HISTOGRAM' operation we first check if the input given after it
is valid, by checking if there are only two tokens and are positive
integers. We then check to have a black and white image loaded
If so, we verify if the number of bins divides 256, and then
split the interval [0,255] into intervals on length 256 / bins. We
created a frequency array to the number of pixels of any value in the
interval [0, 255] and for each of the 'bins' number of intervals we sum
them up. After that we check the maximum number of the sum of each interval
and print a number of stars for each interval, according to the maximum
frequency of all intervals and the user input number of stars.
  * `usage example`: HISTOGRAM 16 16

* For the 'EQUALIZE' operation, we check if we have a black and white image
and if so we create a frequency array for every value in the interval
[0,255] having the matrix of pixels as the given input, and for each pixel
we set them to be equal to the result of the formula given in the problem
text. So as not to have a big complexity we store the partial sum up to
a value in an array of partial sums and we use it in the formula. We obviously
deallocate the array after using it.
  * `usage example`: EQUALIZE
* For the 'ROTATE' operation, we use the functions in the rotate.h header
and check if we have selected the whole image, in which case we rotate
the whole image, or if we have a square selection inside the image, rotate the
selection and put it back into the matrix of pixels. We check if the angle
given is a multiple of 90, situated in absolute value inside [0,360] and if
it is negative, it will be the equivalent of rotating 360-abs(angle). We divide
this by 90 to see how many rotations we will have to do and we call the functions
however many times we need (at most 4).
  * `usage example`: ROTATE 270

