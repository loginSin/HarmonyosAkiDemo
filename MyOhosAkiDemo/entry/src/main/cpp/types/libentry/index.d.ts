export class CppEngine {
  constructor(key: string);
  setDbPath:(db_path: string) => void;
  toString:() => void;
  testCallback:(value: string, func:(result:string) => void) => void;
}