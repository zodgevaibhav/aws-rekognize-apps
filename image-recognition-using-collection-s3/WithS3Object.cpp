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

const Aws::String AK = "AKIAJMR5YCHG7WWRRJ4A";
const Aws::String SK = "m1H5DhVxSXyYBugyGLpbwtdr0fyJRbSYXjvR7y7V";



int main(int argc, char** argv)
{

	Aws::SDKOptions options;
	options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Debug;

	Aws::InitAPI(options);
	{

		Aws::Client::ClientConfiguration clientConfiguration;
		clientConfiguration.region = "us-west-2";
		Aws::Auth::AWSCredentials aws_creds(AK, SK);

		auto rek_client = Aws::MakeShared<Aws::Rekognition::RekognitionClient>(ALLOCATION_TAG, aws_creds, clientConfiguration);


		Aws::Rekognition::Model::S3Object s3Object;
		s3Object.WithBucket("vertex-team")
			.WithName("vz.jpg");

		Aws::Rekognition::Model::Image image;
		image.WithS3Object(s3Object);

		Aws::Rekognition::Model::SearchFacesByImageRequest request;
		request.WithImage(image)
			.WithCollectionId("Vaibhav-Zodge")
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
