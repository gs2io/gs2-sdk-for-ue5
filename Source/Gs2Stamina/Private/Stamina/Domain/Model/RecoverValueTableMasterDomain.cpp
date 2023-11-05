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

#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverValueTableMasterDomain::FRecoverValueTableMasterDomain(
        const Core::Domain::FGs2Ptr Gs2,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RecoverValueTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RecoverValueTableName(RecoverValueTableName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RecoverValueTableMaster"
        ))
    {
    }

    FRecoverValueTableMasterDomain::FRecoverValueTableMasterDomain(
        const FRecoverValueTableMasterDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RecoverValueTableName(From.RecoverValueTableName),
        ParentKey(From.ParentKey)
    {

    }

    FRecoverValueTableMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FRecoverValueTableMasterDomain> Self,
        const Request::FGetRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverValueTableMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverValueTableName(Self->RecoverValueTableName);
        const auto Future = Self->Client->GetRecoverValueTableMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RecoverValueTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FGetTask>> FRecoverValueTableMasterDomain::Get(
        Request::FGetRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRecoverValueTableMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRecoverValueTableMasterDomain> Self,
        const Request::FUpdateRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverValueTableMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverValueTableName(Self->RecoverValueTableName);
        const auto Future = Self->Client->UpdateRecoverValueTableMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RecoverValueTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FUpdateTask>> FRecoverValueTableMasterDomain::Update(
        Request::FUpdateRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRecoverValueTableMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRecoverValueTableMasterDomain> Self,
        const Request::FDeleteRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverValueTableMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverValueTableName(Self->RecoverValueTableName);
        const auto Future = Self->Client->DeleteRecoverValueTableMaster(
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
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "RecoverValueTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FDeleteTask>> FRecoverValueTableMasterDomain::Delete(
        Request::FDeleteRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRecoverValueTableMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RecoverValueTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RecoverValueTableName.IsSet() ? *RecoverValueTableName : "null") + ":" +
            ChildType;
    }

    FString FRecoverValueTableMasterDomain::CreateCacheKey(
        TOptional<FString> RecoverValueTableName
    )
    {
        return FString("") +
            (RecoverValueTableName.IsSet() ? *RecoverValueTableName : "null");
    }

    FRecoverValueTableMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverValueTableMasterDomain> Self
    ): Self(Self)
    {

    }

    FRecoverValueTableMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FRecoverValueTableMaster>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                Self->RecoverValueTableName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetRecoverValueTableMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                    Self->RecoverValueTableName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "recoverValueTableMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FRecoverValueTableMaster>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                    Self->RecoverValueTableName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FModelTask>> FRecoverValueTableMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverValueTableMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRecoverValueTableMasterDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTableMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                RecoverValueTableName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>(obj));
            }
        );
    }

    void FRecoverValueTableMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain::CreateCacheKey(
                RecoverValueTableName
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

