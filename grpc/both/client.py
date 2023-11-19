import grpc
import both_pb2
import both_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = both_pb2_grpc.BothServiceStub(channel)
        number = int(input("Enter a number: "))
        option = int(input('1 - Square\n2 - Cube\n'))

        if option == 1:
            response = stub.GetSquare(both_pb2.SquareRequest(number=number))
        elif option == 2:
            response = stub.GetCube(both_pb2.CubeRequest(number=number))

        print(f"The result of {number} is {response.result}.")

if __name__ == '__main__':
    run()
