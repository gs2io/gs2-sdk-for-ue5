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

#include "Mission/Domain/Model/MissionTaskModelMaster.h"
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

    FMissionTaskModelMasterDomain::FMissionTaskModelMasterDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName,
        const TOptional<FString> MissionTaskName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Session)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        MissionTaskName(MissionTaskName),
        ParentKey(Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
            NamespaceName,
            MissionGroupName,
            "MissionTaskModelMaster"
        ))
    {
    }

    FMissionTaskModelMasterDomain::FMissionTaskModelMasterDomain(
        const FMissionTaskModelMasterDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FMissionTaskModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionTaskModelMasterDomain> Self,
        const Request::FGetMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->GetMissionTaskModelMaster(
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
                const auto ParentKey = Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MissionGroupName,
                    "MissionTaskModelMaster"
                );
                const auto Key = Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FGetTask>> FMissionTaskModelMasterDomain::Get(
        Request::FGetMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMissionTaskModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FMissionTaskModelMasterDomain> Self,
        const Request::FUpdateMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->UpdateMissionTaskModelMaster(
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
                const auto ParentKey = Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MissionGroupName,
                    "MissionTaskModelMaster"
                );
                const auto Key = Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FUpdateTask>> FMissionTaskModelMasterDomain::Update(
        Request::FUpdateMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FMissionTaskModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMissionTaskModelMasterDomain> Self,
        const Request::FDeleteMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->DeleteMissionTaskModelMaster(
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
                const auto ParentKey = Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MissionGroupName,
                    "MissionTaskModelMaster"
                );
                const auto Key = Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Mission::Model::FMissionTaskModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FDeleteTask>> FMissionTaskModelMasterDomain::Delete(
        Request::FDeleteMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FMissionTaskModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        TOptional<FString> MissionTaskName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null") + ":" +
            ChildType;
    }

    FString FMissionTaskModelMasterDomain::CreateCacheKey(
        TOptional<FString> MissionTaskName
    )
    {
        return FString() +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null");
    }

    FMissionTaskModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionTaskModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FMissionTaskModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Mission::Model::FMissionTaskModelMaster>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain::CreateCacheKey(
                Self->MissionTaskName
            )
        );
        if (Value == nullptr) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetMissionTaskModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    if (Future->GetTask().Error()->Detail(0)->GetComponent() == "missionTaskModelMaster")
                    {
                        Self->Cache->Delete(
                            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
                            Self->ParentKey,
                            Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain::CreateCacheKey(
                                Self->MissionTaskName
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
            Value = Self->Cache->Get<Gs2::Mission::Model::FMissionTaskModelMaster>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain::CreateCacheKey(
                    Self->MissionTaskName
                )
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelMasterDomain::FModelTask>> FMissionTaskModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionTaskModelMasterDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

