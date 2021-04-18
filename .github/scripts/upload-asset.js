const fs = require('fs');
const mime = require('mime');

module.exports = ({github, context}) => {

  let upload_url = context.payload.release.upload_url
  upload_url = upload_url.split('{').shift()
  
  const files = process.env.DATA.split(';')
  for (let index in files) {
    const assetPath = files[index]
    const contentType = mime.getType(assetPath);
    const assetName = assetPath.split('/').pop();
    const contentLength = filePath => fs.statSync(filePath).size;
    const headers = { 'content-type': contentType, 'content-length': contentLength(assetPath) };
    const upload_url_with_name = upload_url + '?name=' + assetName
    github.repos.uploadReleaseAsset({
      url: upload_url_with_name,
      headers,
      data: fs.readFileSync(assetPath)
    });
  }
} 
