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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FStackDomain::FStackDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> StackName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Session)),
        StackName(StackName),
        ParentKey("deploy:Stack")
    {
    }

    FStackDomain::FStackDomain(
        const FStackDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FStackDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FStackDomain> Self,
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
        Domain->Status = Domain->Status = ResultModel->GetStatus();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FGetStatusTask>> FStackDomain::GetStatus(
        Request::FGetStackStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FStackDomain::FGetTask::FGetTask(
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Put<Gs2::Deploy::Model::FStack>(
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
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Put<Gs2::Deploy::Model::FStack>(
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

    FStackDomain::FUpdateFromGitHubTask::FUpdateFromGitHubTask(
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Put<Gs2::Deploy::Model::FStack>(
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
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Delete<Gs2::Deploy::Model::FStack>(ParentKey, Key);
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
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Put<Gs2::Deploy::Model::FStack>(
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
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Delete<Gs2::Deploy::Model::FStack>(ParentKey, Key);
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
        const TSharedPtr<FStackDomain> Self,
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
                Self->Cache->Delete<Gs2::Deploy::Model::FStack>(ParentKey, Key);
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

    Gs2::Deploy::Domain::Iterator::FDescribeEventsIteratorPtr FStackDomain::Events(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeEventsIterator>(
            Cache,
            Client,
            StackName
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FEventDomain> FStackDomain::Event(
        const FString EventName
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FEventDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            StackName,
            EventName
        );
    }

    Gs2::Deploy::Domain::Iterator::FDescribeOutputsIteratorPtr FStackDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeOutputsIterator>(
            Cache,
            Client,
            StackName
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FOutputDomain> FStackDomain::Output(
        const FString OutputName
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FOutputDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            StackName,
            OutputName
        );
    }

    Gs2::Deploy::Domain::Iterator::FDescribeResourcesIteratorPtr FStackDomain::Resources(
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeResourcesIterator>(
            Cache,
            Client,
            StackName
        );
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FResourceDomain> FStackDomain::Resource(
        const FString ResourceName
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FResourceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            StackName,
            ResourceName
        );
    }

    FString FStackDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        FString ChildType
    )
    {
        return FString() +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            ChildType;
    }

    FString FStackDomain::CreateCacheKey(
        TOptional<FString> StackName
    )
    {
        return FString() +
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
        auto Value = Self->Cache->Get<Gs2::Deploy::Model::FStack>(
            Self->ParentKey,
            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                Self->StackName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Deploy::Request::FGetStackRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "stack")
                    {
                        Self->Cache->Delete<Gs2::Deploy::Model::FStack>(
                            Self->ParentKey,
                            Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                                Self->StackName
                            )
                        );
                    }
                    else
                    {
                        return Future->GetTask().Error();
                    }
                }
                else
                {
                    return Future->GetTask().Error();
                }
            }
            Value = Self->Cache->Get<Gs2::Deploy::Model::FStack>(
                Self->ParentKey,
                Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheKey(
                    Self->StackName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStackDomain::FModelTask>> FStackDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStackDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

