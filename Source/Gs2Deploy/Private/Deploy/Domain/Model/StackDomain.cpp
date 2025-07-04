/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Deploy::Domain::Model
{

    FStackDomain::FStackDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Deploy::Domain::FGs2DeployDomainPtr& Service,
        const TOptional<FString> StackName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        StackName(StackName),
        ParentKey("deploy:Stack")
    {
    }

    FStackDomain::FStackDomain(
        const FStackDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StackName(From.StackName),
        ParentKey(From.ParentKey)
    {

    }

    FStackDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FGetStackStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->GetStackStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FGetStatusTask>> FStackDomain::GetStatus(
        Request::FGetStackStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FStackDomain::FGetTask::FGetTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FGetStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FStack>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->GetStack(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FGetTask>> FStackDomain::Get(
        Request::FGetStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStackDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FUpdateStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->UpdateStack(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FUpdateTask>> FStackDomain::Update(
        Request::FUpdateStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FStackDomain::FChangeSetTask::FChangeSetTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FChangeSetRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FChangeSetTask::FChangeSetTask(
        const FChangeSetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FChangeSetTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Deploy::Model::FChangeSet>>>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->ChangeSet(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        *Result = ResultModel->GetItems();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FChangeSetTask>> FStackDomain::ChangeSet(
        Request::FChangeSetRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FChangeSetTask>>(this->AsShared(), Request);
    }

    FStackDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FUpdateStackFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const FUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->UpdateStackFromGitHub(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FUpdateFromGitHubTask>> FStackDomain::UpdateFromGitHub(
        Request::FUpdateStackFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FStackDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FDeleteStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->DeleteStack(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Deploy::Model::FStack::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FDeleteTask>> FStackDomain::Delete(
        Request::FDeleteStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FStackDomain::FForceDeleteTask::FForceDeleteTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FForceDeleteStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FForceDeleteTask::FForceDeleteTask(
        const FForceDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FForceDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->ForceDeleteStack(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FForceDeleteTask>> FStackDomain::ForceDelete(
        Request::FForceDeleteStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FForceDeleteTask>>(this->AsShared(), Request);
    }

    FStackDomain::FDeleteResourcesTask::FDeleteResourcesTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FDeleteStackResourcesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FDeleteResourcesTask::FDeleteResourcesTask(
        const FDeleteResourcesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FDeleteResourcesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->DeleteStackResources(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Deploy::Model::FStack::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FDeleteResourcesTask>> FStackDomain::DeleteResources(
        Request::FDeleteStackResourcesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteResourcesTask>>(this->AsShared(), Request);
    }

    FStackDomain::FDeleteEntityTask::FDeleteEntityTask(
        const TSharedPtr<FStackDomain>& Self,
        const Request::FDeleteStackEntityRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStackDomain::FDeleteEntityTask::FDeleteEntityTask(
        const FDeleteEntityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FDeleteEntityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        Request
            ->WithStackName(Self->StackName);
        const auto Future = Self->Client->DeleteStackEntity(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            {
                const auto ParentKey = FString("deploy:Stack");
                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Deploy::Model::FStack::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FDeleteEntityTask>> FStackDomain::DeleteEntity(
        Request::FDeleteStackEntityRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteEntityTask>>(this->AsShared(), Request);
    }

    Gs2::Deploy::Domain::Iterator::FDescribeResourcesIteratorPtr FStackDomain::Resources(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeResourcesIterator>(
            Gs2,
            Client,
            StackName
        );
    }

    Gs2::Core::Domain::CallbackID FStackDomain::SubscribeResources(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Deploy::Model::FResource::TypeName,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                StackName,
                "Resource"
            ),
            Callback
        );
    }

    void FStackDomain::UnsubscribeResources(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Deploy::Model::FResource::TypeName,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                StackName,
                "Resource"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FResourceDomain> FStackDomain::Resource(
        const FString ResourceName
    )
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FResourceDomain>(
            Gs2,
            Service,
            StackName,
            ResourceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(ResourceName)
        );
    }

    Gs2::Deploy::Domain::Iterator::FDescribeEventsIteratorPtr FStackDomain::Events(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeEventsIterator>(
            Gs2,
            Client,
            StackName
        );
    }

    Gs2::Core::Domain::CallbackID FStackDomain::SubscribeEvents(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Deploy::Model::FEvent::TypeName,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                StackName,
                "Event"
            ),
            Callback
        );
    }

    void FStackDomain::UnsubscribeEvents(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Deploy::Model::FEvent::TypeName,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                StackName,
                "Event"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FEventDomain> FStackDomain::Event(
        const FString EventName
    )
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FEventDomain>(
            Gs2,
            Service,
            StackName,
            EventName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EventName)
        );
    }

    Gs2::Deploy::Domain::Iterator::FDescribeOutputsIteratorPtr FStackDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeOutputsIterator>(
            Gs2,
            Client,
            StackName
        );
    }

    Gs2::Core::Domain::CallbackID FStackDomain::SubscribeOutputs(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Deploy::Model::FOutput::TypeName,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                StackName,
                "Output"
            ),
            Callback
        );
    }

    void FStackDomain::UnsubscribeOutputs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Deploy::Model::FOutput::TypeName,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
                StackName,
                "Output"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FOutputDomain> FStackDomain::Output(
        const FString OutputName
    )
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FOutputDomain>(
            Gs2,
            Service,
            StackName,
            OutputName == TEXT("") ? TOptional<FString>() : TOptional<FString>(OutputName)
        );
    }

    FString FStackDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        FString ChildType
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            ChildType;
    }

    FString FStackDomain::CreateCacheKey(
        TOptional<FString> StackName
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null");
    }

    FStackDomain::FModelTask::FModelTask(
        const TSharedPtr<FStackDomain> Self
    ): Self(Self)
    {

    }

    FStackDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStackDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FStack>> Result
    )
    {
        const auto ParentKey = FString("deploy:Stack");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Deploy::Model::FStack> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Deploy::Model::FStack>(
            ParentKey,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                Self->StackName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Deploy::Request::FGetStackRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    Self->StackName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FStack::TypeName,
                    ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "stack")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Deploy::Model::FStack>(
                ParentKey,
                Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    Self->StackName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FModelTask>> FStackDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStackDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStackDomain::Subscribe(
        TFunction<void(Gs2::Deploy::Model::FStackPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Deploy::Model::FStack::TypeName,
            ParentKey,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                StackName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Deploy::Model::FStack>(obj));
            }
        );
    }

    void FStackDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Deploy::Model::FStack::TypeName,
            ParentKey,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                StackName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

