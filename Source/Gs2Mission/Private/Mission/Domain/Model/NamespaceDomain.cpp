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

#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Session)),
        NamespaceName(NamespaceName),
        ParentKey("mission:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FNamespace>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
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
                const auto ParentKey = FString("mission:Namespace");
                const auto Key = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FNamespace::TypeName,
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
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
                const auto ParentKey = FString("mission:Namespace");
                const auto Key = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FNamespace::TypeName,
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
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
                const auto ParentKey = FString("mission:Namespace");
                const auto Key = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Mission::Model::FNamespace::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateMissionGroupModelMasterTask::FCreateMissionGroupModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateMissionGroupModelMasterTask::FCreateMissionGroupModelMasterTask(
        const FCreateMissionGroupModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateMissionGroupModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateMissionGroupModelMaster(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "MissionGroupModelMaster"
                );
                const auto Key = Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateMissionGroupModelMasterTask>> FNamespaceDomain::CreateMissionGroupModelMaster(
        Request::FCreateMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateMissionGroupModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateCounterModelMasterTask::FCreateCounterModelMasterTask(
        const TSharedPtr<FNamespaceDomain> Self,
        const Request::FCreateCounterModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateCounterModelMasterTask::FCreateCounterModelMasterTask(
        const FCreateCounterModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateCounterModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FCounterModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateCounterModelMaster(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "CounterModelMaster"
                );
                const auto Key = Gs2::Mission::Domain::Model::FCounterModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FCounterModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Mission::Domain::Model::FCounterModelMasterDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateCounterModelMasterTask>> FNamespaceDomain::CreateCounterModelMaster(
        Request::FCreateCounterModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateCounterModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FCurrentMissionMasterDomain> FNamespaceDomain::CurrentMissionMaster(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FCurrentMissionMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    Gs2::Mission::Domain::Iterator::FDescribeMissionGroupModelsIteratorPtr FNamespaceDomain::MissionGroupModels(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeMissionGroupModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelDomain> FNamespaceDomain::MissionGroupModel(
        const FString MissionGroupName
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FMissionGroupModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            MissionGroupName
        );
    }

    Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIteratorPtr FNamespaceDomain::CounterModels(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FCounterModelDomain> FNamespaceDomain::CounterModel(
        const FString CounterName
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FCounterModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            CounterName
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FUserDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FUserAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Mission::Domain::Iterator::FDescribeMissionGroupModelMastersIteratorPtr FNamespaceDomain::MissionGroupModelMasters(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeMissionGroupModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain> FNamespaceDomain::MissionGroupModelMaster(
        const FString MissionGroupName
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            MissionGroupName
        );
    }

    Gs2::Mission::Domain::Iterator::FDescribeCounterModelMastersIteratorPtr FNamespaceDomain::CounterModelMasters(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeCounterModelMastersIterator>(
            Cache,
            Client,
            NamespaceName
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FCounterModelMasterDomain> FNamespaceDomain::CounterModelMaster(
        const FString CounterName
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FCounterModelMasterDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            CounterName
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("mission:Namespace");
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FNamespace> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Mission::Model::FNamespace>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                Self->NamespaceName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetNamespaceRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FNamespace::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "namespace")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Mission::Model::FNamespace>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    Self->NamespaceName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

