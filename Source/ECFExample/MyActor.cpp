#include "MyActor.h"
#include "HttpModule.h"

void AMyActor::MultipleExecsFuncion(EInExecType Exec, EOutExecType& Then)
{

}

AActor* AMyActor::CreateActorOfClass(TSubclassOf<AActor> ActorClass)
{
	return GetWorld()->SpawnActor<AActor>(ActorClass);
}

void AMyActor::CreateManyActorsOfClass(TSubclassOf<AActor> ActorClass, TArray<AActor*>& Actors)
{
	for (int32 i = 0; i < 3; i++)
	{
		Actors.Add(GetWorld()->SpawnActor<AActor>(ActorClass));
	}
}
