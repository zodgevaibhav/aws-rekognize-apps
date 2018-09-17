#include <aws/core/Aws.h>
#include<aws\core\utils\FileSystemUtils.h>
#include<aws\core\utils\Outcome.h>
#include<aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/utils/logging/DefaultLogSystem.h>
#include <aws/core/utils/logging/AWSLogging.h>
#include<aws\core\http\HttpRequest.h>

#include<aws\rekognition\RekognitionClient.h>
#include<aws\rekognition\model\SearchFacesByImageRequest.h>
#include<aws\rekognition\model\Image.h>


#pragma comment(lib,"aws-cpp-sdk-core.lib")
#pragma comment(lib,"aws-cpp-sdk-rekognition.lib")


static const char* ALLOCATION_TAG = "RekognizeSample::Main";


int main(int argc, char** argv)
{



	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Debug;

	Aws::InitAPI(options);
	{

		 Aws::String AK;
		 Aws::String SK;

		char* buf = nullptr;
		size_t sz = 0;

		if (_dupenv_s(&buf, &sz, "AWS_ACCESS_KEY_ID") == 0 && buf != nullptr)
		{
			AK = buf;
		}
		
		if (_dupenv_s(&buf, &sz, "AWS_SECRET_ACCESS_KEY") == 0 && buf != nullptr)
		{
			SK = buf;
			free(buf);
		}

		

		Aws::Client::ClientConfiguration clientConfiguration;
		clientConfiguration.region = "us-west-2";
		Aws::Auth::AWSCredentials aws_creds(AK, SK);

		auto rek_client = Aws::MakeShared<Aws::Rekognition::RekognitionClient>(ALLOCATION_TAG, aws_creds, clientConfiguration);


		Aws::Rekognition::Model::S3Object s3Object;
		s3Object.WithBucket("vertex-team") //bucket needs to create in AWS S3 using console
			.WithName("vz.jpg"); //image is uploaded on S3

		Aws::Rekognition::Model::Image image;
		image.WithS3Object(s3Object);

		Aws::Rekognition::Model::SearchFacesByImageRequest request;
		request.WithImage(image)
			.WithCollectionId("Vaibhav-Zodge") //collection needs to create using api's, which contain images with faces. Sample java code available https://github.com/zodgevaibhav/aws-lex-poly-rekgonition-demo
			.WithFaceMatchThreshold(70)
			.WithMaxFaces(2);

		Aws::Rekognition::Model::SearchFacesByImageResult result = rek_client->SearchFacesByImage(request).GetResultWithOwnership();

		Aws::Vector<Aws::Rekognition::Model::FaceMatch> vecMatch =  result.GetFaceMatches();

		Aws::Rekognition::Model::Face match = vecMatch[0].GetFace();

		std::cout << std::endl << std::endl;
		std::cout << "Image ID is : " << match.GetImageId()<<std::endl;
		std::cout << "Face id is : " << match.GetFaceId() << std::endl;
		std::cout << "Confidence is : " << match.GetConfidence() << std::endl;
		std::cout << "External Image ID is : " << match.GetExternalImageId() << std::endl;
	}
	Aws::ShutdownAPI(options);
}
