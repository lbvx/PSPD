import grpc
import square_pb2
import square_pb2_grpc

def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = square_pb2_grpc.SquareServiceStub(channel)
        number = int(input("Enter a number: "))
        response = stub.GetSquare(square_pb2.SquareRequest(number=number))
        print(f"The square of {number} is {response.result}.")

if __name__ == '__main__':
    run()
