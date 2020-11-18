pragma solidity 0.5;
pragma experimental ABIEncoderV2;

contract KUContract  {
    address public owner;
    bool private beforeInit;
    
    string hiddenFlag = ""; /* TOP SECRET */

    uint8[] flag;
    
    mapping(uint16 => string) uintToString;
    
    mapping(address => int) money;
    string moneyFlag;
    
    constructor(uint8[] memory f, string memory s, string memory a) public {
        owner = msg.sender;
        flag = f;
        uint16 idx = uint16(now % 50000);
        uintToString[idx] = s;
        moneyFlag = a;
    }
    
     modifier onlyOwner() {
        require(msg.sender == owner);
        _;
    }
    
    function getMyFlag() public view returns (uint8[] memory) {
        uint8[] memory encryptedFlag = new uint8[](27);
        uint8 key = uint8(msg.sender);
        for(uint i=0; i<27; i++) {
            encryptedFlag[i] = flag[i] ^ key;
        }
        
        return encryptedFlag;
    }
    
    function guessIndex(uint16 idx) public view returns (string memory) {
        return uintToString[idx];
    }
    
    function getMoney() public returns (bool) {
        money[msg.sender] = 2000;
        return true;
    }
    
    function playGame(uint8 choice) public returns (bool) {
        require(choice <= 1);
        uint randomNumber = uint(keccak256(abi.encodePacked(now, msg.sender))) % 2;
        if (randomNumber == choice) {
            money[msg.sender] += 100;
        } else {
            money[msg.sender] -= 100;
        }
        return true;
    }
    
    function showMoney() public view returns (int) {
        return money[msg.sender];
    }
    
    function richGetFlag() public view returns(string memory) {
        uint256 m = uint256(money[msg.sender]);
        if(m >= 1000000) {
            return moneyFlag;
        }
        return "";
    }
    
    function getNoew() public view returns(uint256,uint8) {
        return (now, uint8(now));
    }
}