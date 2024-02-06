import hilog from '@ohos.hilog';
import testNapi from 'libentry.so'

@Entry
@Component
struct Index {
  @State message: string = 'Hello World'
  engine:testNapi.CppEngine = null;

  build() {
    Row() {
      Column() {
        Button("创建")
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.engine = new testNapi.CppEngine("testKey");
            hilog.info(0x0000, 'CppEngine-js', '创建');
          })
        Button("设置路径")
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.engine.setDbPath("path/to/db");
            hilog.info(0x0000, 'CppEngine-js', '设置路径');
          })
        Button("打印信息")
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            this.engine.toString();
            hilog.info(0x0000, 'CppEngine-js', '打印信息');
          })
        Button("调用Callback")
          .fontSize(50)
          .fontWeight(FontWeight.Bold)
          .onClick(() => {
            hilog.info(0x0000, 'CppEngine-js', '调用Callback接口');
            this.engine.testCallback("testValue",(result) => {
              hilog.info(0x0000, 'CppEngine-js', 'Callback回调结果 ' + result);
            });
          })
      }
      .width('100%')
    }
    .height('100%')
  }
}
