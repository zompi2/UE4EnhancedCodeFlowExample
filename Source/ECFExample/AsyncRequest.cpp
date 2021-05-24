#include "AsyncRequest.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"

UAsyncRequest* UAsyncRequest::AsyncRequest(UObject* WorldContextObject, FString InURL)
{
	UAsyncRequest* Proxy = NewObject<UAsyncRequest>();

	Proxy->Proxy_WorldContextObject = WorldContextObject;
	Proxy->Proxy_URL = InURL;

	return Proxy;
}

void UAsyncRequest::Activate()
{
	FHttpRequestRef HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(Proxy_URL);
	HttpRequest->SetVerb(TEXT("GET"));

	TWeakObjectPtr<ThisClass> WeakThis(this);
	HttpRequest->OnProcessRequestComplete().BindLambda([WeakThis](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bSucceeded)
	{
		if (ThisClass* StrongThis = WeakThis.Get())
		{
			StrongThis->OnComplete.Broadcast(bSucceeded);
		}
	});

	HttpRequest->ProcessRequest();
}
