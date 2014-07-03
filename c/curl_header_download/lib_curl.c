//gcc -lcurl -o lib_curl lib_curl.c; ./lib_curl
#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


size_t recieve_header(void *ptr, size_t size, size_t nmemb, void *stream);

curl_version_info_data* data;
CURLcode init;
CURL* easy_hndl;
CURLcode conct;

FILE* header_data;

struct curl_httppost* formpost = NULL;
struct curl_httppost* std_post = NULL;
struct curl_slist* headerlist = NULL;

int main(int argc, char* argv[])
{

    if((open("header.txt", O_APPEND, O_RDWR)) == -1)
    {
        perror("File could not open");
        exit(0);
    }
    init = curl_global_init(CURL_GLOBAL_ALL);
    easy_hndl = curl_easy_init( );
    data = curl_version_info(CURLVERSION_NOW);
    printf("You are using curl version: %d\n", data->age);
    printf("You are running curl version: %s\n", data->version);
    printf("The host is: %s\n", data->host);
    printf("The SSL version is: %s\n", data->ssl_version);
    printf("You are running SSL version: %d\n", data->ssl_version);
    printf("Ares is :%s\n", data->ares);
    printf("Ares_num is: %d\n", data->ares_num);
    printf("iconv_ver_num is: %d\n", data->iconv_ver_num);
    printf("libssh_version num is: %s\n", data->libssh_version);


    /*  Set the URL   */
    curl_easy_setopt(easy_hndl, CURLOPT_URL, "http://www.geoginfo.com/");
    //"http://factfinder.census.gov/servlet/DTTable?_bm=y&-context=dt&-ds_name=DEC_2000_SF1_U&-CHECK_SEARCH_RESULTS=N&-mt_name=DEC_2000_SF1_U_P001&-mt_name=DEC_2000_SF1_U_P002&-mt_name=DEC_2000_SF1_U_P003&-CONTEXT=dt&-tree_id=4001&-all_geo_types=N&-geo_id=05000US06001&-geo_id=05000US06003&-geo_id=05000US06005&-geo_id=05000US06007&-geo_id=05000US06009&-geo_id=05000US06011&-geo_id=05000US06013&-geo_id=05000US06015&-geo_id=05000US06017&-geo_id=05000US06019&-geo_id=05000US06021&-geo_id=05000US06023&-geo_id=05000US06025&-geo_id=05000US06027&-geo_id=05000US06029&-geo_id=05000US06031&-geo_id=05000US06033&-geo_id=05000US06035&-geo_id=05000US06037&-geo_id=05000US06039&-geo_id=05000US06041&-geo_id=05000US06043&-geo_id=05000US06045&-geo_id=05000US06047&-geo_id=05000US06049&-geo_id=05000US06051&-geo_id=05000US06053&-geo_id=05000US06055&-geo_id=05000US06057&-geo_id=05000US06059&-geo_id=05000US06061&-geo_id=05000US06063&-geo_id=05000US06065&-geo_id=05000US06067&-geo_id=05000US06069&-geo_id=05000US06071&-geo_id=05000US06073&-geo_id=05000US06075&-geo_id=05000US06077&-geo_id=05000US06079&-geo_id=05000US06081&-geo_id=05000US06083&-geo_id=05000US06085&-geo_id=05000US06087&-geo_id=05000US06089&-geo_id=05000US06091&-geo_id=05000US06093&-geo_id=05000US06095&-geo_id=05000US06097&-geo_id=05000US06099&-geo_id=05000US06101&-geo_id=05000US06103&-geo_id=05000US06105&-geo_id=05000US06107&-geo_id=05000US06109&-geo_id=05000US06111&-geo_id=05000US06113&-geo_id=05000US06115&-format=&-_lang=en");

    /*  Now perform a special POST  */
    //headerlist = curl_slist_append(headerlist, "This is a test");
    //curl_easy_setopt(easy_hndl, CURLOPT_HTTPPOST, headerlist);

    /*  Now perform a normal GET    */
    curl_easy_setopt(easy_hndl, CURLOPT_WRITEHEADER, header_data);
    curl_easy_setopt(easy_hndl, CURLOPT_HEADERFUNCTION, recieve_header);
    printf("\n\n\nRESPONSE HEADER=========================================================================================\n");
    conct = curl_easy_perform(easy_hndl);
    printf("=========================================================================================================\n");


    curl_easy_cleanup(easy_hndl);
    curl_global_cleanup();
	return 0;
}

size_t recieve_header(void* ptr, size_t size, size_t nmemb, void* stream)
{
    printf("%s", ptr);
    return size*nmemb;
}
