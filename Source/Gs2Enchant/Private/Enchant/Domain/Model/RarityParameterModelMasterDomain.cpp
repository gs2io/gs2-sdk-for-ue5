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

#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FRarityParameterModelMasterDomain::FRarityParameterModelMasterDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ParameterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParameterName(ParameterName),
        ParentKey(Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RarityParameterModelMaster"
        ))
    {
    }

    FRarityParameterModelMasterDomain::FRarityParameterModelMasterDomain(
        const FRarityParameterModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParameterName(From.ParameterName),
        ParentKey(From.ParentKey)
    {

    }

    FRarityParameterModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FRarityParameterModelMasterDomain> Self,
        const Request::FGetRarityParameterModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModelMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName);
        const auto Future = Self->Client->GetRarityParameterModelMaster(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RarityParameterModelMaster"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterModelMasterDomain::FGetTask>> FRarityParameterModelMasterDomain::Get(
        Request::FGetRarityParameterModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRarityParameterModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRarityParameterModelMasterDomain> Self,
        const Request::FUpdateRarityParameterModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName);
        const auto Future = Self->Client->UpdateRarityParameterModelMaster(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RarityParameterModelMaster"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterModelMasterDomain::FUpdateTask>> FRarityParameterModelMasterDomain::Update(
        Request::FUpdateRarityParameterModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRarityParameterModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRarityParameterModelMasterDomain> Self,
        const Request::FDeleteRarityParameterModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName);
        const auto Future = Self->Client->DeleteRarityParameterModelMaster(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RarityParameterModelMaster"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterModelMasterDomain::FDeleteTask>> FRarityParameterModelMasterDomain::Delete(
        Request::FDeleteRarityParameterModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRarityParameterModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ParameterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ParameterName.IsSet() ? *ParameterName : "null") + ":" +
            ChildType;
    }

    FString FRarityParameterModelMasterDomain::CreateCacheKey(
        TOptional<FString> ParameterName
    )
    {
        return FString("") +
            (ParameterName.IsSet() ? *ParameterName : "null");
    }

    FRarityParameterModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FRarityParameterModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FRarityParameterModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModelMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Enchant::Model::FRarityParameterModelMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Enchant::Model::FRarityParameterModelMaster>(
            Self->ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                Self->ParameterName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enchant::Request::FGetRarityParameterModelMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                    Self->ParameterName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "rarityParameterModelMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Enchant::Model::FRarityParameterModelMaster>(
                Self->ParentKey,
                Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                    Self->ParameterName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterModelMasterDomain::FModelTask>> FRarityParameterModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRarityParameterModelMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRarityParameterModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Enchant::Model::FRarityParameterModelMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
            ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                ParameterName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enchant::Model::FRarityParameterModelMaster>(obj));
            }
        );
    }

    void FRarityParameterModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Enchant::Model::FRarityParameterModelMaster::TypeName,
            ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterModelMasterDomain::CreateCacheKey(
                ParameterName
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

