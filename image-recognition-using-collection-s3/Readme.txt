1. The code have dependency on aws-cpp-sdk-core and aws-cpp-sdk-rekognition
2. Checkout and build these two project from "https://github.com/aws/aws-sdk-cpp"
3. Include file from both the project>include folder, include libraries and put dll at required place (I kept in debug folder for try out)
4. Setup AWS credentials in environment variable as per code