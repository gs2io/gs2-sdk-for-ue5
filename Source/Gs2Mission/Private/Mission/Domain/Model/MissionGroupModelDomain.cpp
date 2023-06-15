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

#include "Mission/Domain/Model/MissionGroupModel.h"
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

    FMissionGroupModelDomain::FMissionGroupModelDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Session)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        ParentKey(Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MissionGroupModel"
        ))
    {
    }

    FMissionGroupModelDomain::FMissionGroupModelDomain(
        const FMissionGroupModelDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FMissionGroupModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionGroupModelDomain> Self,
        const Request::FGetMissionGroupModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModel>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->GetMissionGroupModel(
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
                    "MissionGroupModel"
                );
                const auto Key = Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FMissionGroupModel::TypeName,
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

    TSharedPtr<FAsyncTask<FMissionGroupModelDomain::FGetTask>> FMissionGroupModelDomain::Get(
        Request::FGetMissionGroupModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIteratorPtr FMissionGroupModelDomain::MissionTaskModels(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator>(
            Cache,
            Client,
            NamespaceName,
            MissionGroupName
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelDomain> FMissionGroupModelDomain::MissionTaskModel(
        const FString MissionTaskName
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Model::FMissionTaskModelDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            MissionGroupName,
            MissionTaskName
        );
    }

    FString FMissionGroupModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            ChildType;
    }

    FString FMissionGroupModelDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString() +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FMissionGroupModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionGroupModelDomain> Self
    ): Self(Self)
    {

    }

    FMissionGroupModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FMissionGroupModel> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Mission::Model::FMissionGroupModel>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheKey(
                Self->MissionGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetMissionGroupModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheKey(
                    Self->MissionGroupName
                );
                Self->Cache->Put(
                    Gs2::Mission::Model::FMissionGroupModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "missionGroupModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Mission::Model::FMissionGroupModel>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheKey(
                    Self->MissionGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelDomain::FModelTask>> FMissionGroupModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionGroupModelDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

