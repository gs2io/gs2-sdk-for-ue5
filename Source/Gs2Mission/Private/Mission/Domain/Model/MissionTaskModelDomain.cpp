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

#include "Mission/Domain/Model/MissionTaskModel.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FMissionTaskModelDomain::FMissionTaskModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName,
        const TOptional<FString> MissionTaskName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        MissionTaskName(MissionTaskName),
        ParentKey(Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheParentKey(
            NamespaceName,
            MissionGroupName,
            "MissionTaskModel"
        ))
    {
    }

    FMissionTaskModelDomain::FMissionTaskModelDomain(
        const FMissionTaskModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MissionGroupName(From.MissionGroupName),
        MissionTaskName(From.MissionTaskName),
        ParentKey(From.ParentKey)
    {

    }

    FMissionTaskModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionTaskModelDomain>& Self,
        const Request::FGetMissionTaskModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionTaskModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName)
            ->WithMissionTaskName(Self->MissionTaskName);
        const auto Future = Self->Client->GetMissionTaskModel(
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
                const auto ParentKey = Gs2::Mission::Domain::Model::FMissionGroupModelDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->MissionGroupName,
                    "MissionTaskModel"
                );
                const auto Key = Gs2::Mission::Domain::Model::FMissionTaskModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FMissionTaskModel::TypeName,
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

    TSharedPtr<FAsyncTask<FMissionTaskModelDomain::FGetTask>> FMissionTaskModelDomain::Get(
        Request::FGetMissionTaskModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FMissionTaskModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        TOptional<FString> MissionTaskName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null") + ":" +
            ChildType;
    }

    FString FMissionTaskModelDomain::CreateCacheKey(
        TOptional<FString> MissionTaskName
    )
    {
        return FString("") +
            (MissionTaskName.IsSet() ? *MissionTaskName : "null");
    }

    FMissionTaskModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionTaskModelDomain> Self
    ): Self(Self)
    {

    }

    FMissionTaskModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionTaskModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionTaskModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FMissionTaskModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FMissionTaskModel>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FMissionTaskModelDomain::CreateCacheKey(
                Self->MissionTaskName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetMissionTaskModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FMissionTaskModelDomain::CreateCacheKey(
                    Self->MissionTaskName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FMissionTaskModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "missionTaskModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FMissionTaskModel>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FMissionTaskModelDomain::CreateCacheKey(
                    Self->MissionTaskName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionTaskModelDomain::FModelTask>> FMissionTaskModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionTaskModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMissionTaskModelDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FMissionTaskModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FMissionTaskModelDomain::CreateCacheKey(
                MissionTaskName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FMissionTaskModel>(obj));
            }
        );
    }

    void FMissionTaskModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FMissionTaskModelDomain::CreateCacheKey(
                MissionTaskName
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

