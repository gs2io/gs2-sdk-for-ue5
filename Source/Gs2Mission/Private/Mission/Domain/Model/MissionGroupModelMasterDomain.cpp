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

#include "Mission/Domain/Model/MissionGroupModelMaster.h"
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

    FMissionGroupModelMasterDomain::FMissionGroupModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        ParentKey(Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MissionGroupModelMaster"
        ))
    {
    }

    FMissionGroupModelMasterDomain::FMissionGroupModelMasterDomain(
        const FMissionGroupModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MissionGroupName(From.MissionGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FMissionGroupModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FGetMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->GetMissionGroupModelMaster(
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
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FGetTask>> FMissionGroupModelMasterDomain::Get(
        Request::FGetMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMissionGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FUpdateMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->UpdateMissionGroupModelMaster(
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
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FUpdateTask>> FMissionGroupModelMasterDomain::Update(
        Request::FUpdateMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FMissionGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FDeleteMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->DeleteMissionGroupModelMaster(
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
                Self->Gs2->Cache->Delete(Gs2::Mission::Model::FMissionGroupModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FDeleteTask>> FMissionGroupModelMasterDomain::Delete(
        Request::FDeleteMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask::FCreateMissionTaskModelMasterTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FCreateMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask::FCreateMissionTaskModelMasterTask(
        const FCreateMissionTaskModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->CreateMissionTaskModelMaster(
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
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask>> FMissionGroupModelMasterDomain::CreateMissionTaskModelMaster(
        Request::FCreateMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateMissionTaskModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelMastersIteratorPtr FMissionGroupModelMasterDomain::MissionTaskModelMasters(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelMastersIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            MissionGroupName
        );
    }

    Gs2::Core::Domain::CallbackID FMissionGroupModelMasterDomain::SubscribeMissionTaskModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
                NamespaceName,
                MissionGroupName,
                "MissionTaskModelMaster"
            ),
            Callback
        );
    }

    void FMissionGroupModelMasterDomain::UnsubscribeMissionTaskModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheParentKey(
                NamespaceName,
                MissionGroupName,
                "MissionTaskModelMaster"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain> FMissionGroupModelMasterDomain::MissionTaskModelMaster(
        const FString MissionTaskName
    )
    {
        return MakeShared<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            MissionGroupName,
            MissionTaskName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MissionTaskName)
        );
    }

    FString FMissionGroupModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            ChildType;
    }

    FString FMissionGroupModelMasterDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString("") +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FMissionGroupModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionGroupModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FMissionGroupModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FMissionGroupModelMaster>(
            Self->ParentKey,
            Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheKey(
                Self->MissionGroupName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Mission::Request::FGetMissionGroupModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheKey(
                    Self->MissionGroupName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "missionGroupModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Mission::Model::FMissionGroupModelMaster>(
                Self->ParentKey,
                Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheKey(
                    Self->MissionGroupName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FModelTask>> FMissionGroupModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionGroupModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FMissionGroupModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheKey(
                MissionGroupName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>(obj));
            }
        );
    }

    void FMissionGroupModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
            ParentKey,
            Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain::CreateCacheKey(
                MissionGroupName
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

