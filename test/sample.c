/*
 * sample code with libchardet
 * author: JoungKyun.Kim <http://oops.org>
 * $Id$
 */

#include <chardet.h>
//#include "../src/chardet.h"

int main (void) {
	Detect * d;
	DetectObj *obj;
	int i;

	char *str[] = {
		"안녕",
		"안녕하세요",
		"안녕하세요 정말?",
		"그래 이정도면 판단 될까?",
		"좀더 길게 적어 볼까 얼마나 길게 해야!",
		"그래 그래 좀 더 길게 적어 보자 더 길게 적어 보야야 겠지...",
		"12345 abcde"
	};

	short arrayNum;
	arrayNum = sizeof (str) / sizeof (str[0]);

	if ( (d = detect_init ()) == NULL ) {
		fprintf (stderr, "chardet handle initialize failed\n");
		return CHARDET_MEM_ALLOCATED_FAIL;
	}

	for ( i=0; i<arrayNum; i++ ) {
		detect_reset (&d);

		obj = detect_obj_init ();
		if ( obj == NULL ) {
			fprintf (stderr, "On attemped \"%s\", memory allocation failed\n", str[i]);
			continue;
		}

#ifdef CHARDET_BINARY_SAFE
		if ( detect_handledata_r (&d, str[i], strlen (str[i]), &obj) == CHARDET_OUT_OF_MEMORY )
#else
		if ( detect_handledata (&d, str[i], &obj) == CHARDET_OUT_OF_MEMORY )
#endif
		{
			fprintf (stderr, "On handle processing, occured out of memory\n");
			return CHARDET_OUT_OF_MEMORY;
		}
		printf ("## %s : %s : %f\n", str[i], obj->encoding, obj->confidence);
		detect_obj_free (&obj);
	}

	detect_destroy (&d);

	return 0;
}
