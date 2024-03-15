# Project made by Bărnuț Cristiana
import functions


def test_addition():
    assert functions.addition('11100111001110101', '1101111011111', 2) == '11110101001010100'
    assert functions.addition('23045', '100254', 6) == '123343'
    assert functions.addition('54AB6F', 'CD097D', 16) == '121B4EC'
    assert functions.addition('2122012', '10112222', 3) == '20012011'
    assert functions.addition('3220013', '22303231', 4) == '32123310'
    assert functions.addition('3401323', '444033', 5) == '4400411'
    assert functions.addition('6543210', '664455', 7) == '10540665'
    assert functions.addition('5677034', '1234567', 8) == '7133623'
    assert functions.addition('ABCDE', 'D9037F', 16) == 'E3C05D'
    assert functions.addition('1100101011', '11101101', 2) == '10000011000'


def test_subtraction():
    assert functions.subtraction('10001100010', '1110111011', 2) == '10100111'
    assert functions.subtraction('102387', '64502', 9) == '26785'
    assert functions.subtraction('501BA', '32ED', 16) == '4CECD'
    assert functions.subtraction('130046', '71257', 8) == '36567'
    assert functions.subtraction('210354', '55466', 7) == '121555'
    assert functions.subtraction('210354', '44355', 6) == '121555'
    assert functions.subtraction('102003', '3333', 5) == '43120'
    assert functions.subtraction('102003', '3333', 4) == '32010'
    assert functions.subtraction('100111000', '1100111', 2) == '11010001'
    assert functions.subtraction('10B009', 'A5FCD', 16) == '6503C'


def test_multiplication():
    assert functions.multiplication('7023', '5', 8) == '43137'
    assert functions.multiplication('32001B', '6', 16) == '12C00A2'
    assert functions.multiplication('12345', '5', 7) == '65424'
    assert functions.multiplication('12345', '5', 6) == '111101'
    assert functions.multiplication('31203', '3', 5) == '144114'
    assert functions.multiplication('31203', '3', 4) == '220221'
    assert functions.multiplication('21563', '7', 8) == '174045'
    assert functions.multiplication('A23F4', 'B', 16) == '6F8B7C'


def test_division():
    assert functions.division('20101', '2', 3) == ('10012', '0')
    assert functions.division('1FED0205', '9', 16) == ('38C1CAB', '2')
    assert functions.division('120456', '6', 8) == ('15335', '0')
    assert functions.division('120456', '6', 7) == ('13421', '0')
    assert functions.division('321023', '3', 5) == ('103322', '2')
    assert functions.division('321023', '3', 4) == ('103003', '2')
    assert functions.division('2A0F86', 'E', 16) == ('3011B', 'C')
    assert functions.division('765433', '4', 8) == ('175306', '3')
