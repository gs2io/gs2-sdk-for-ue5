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

#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
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
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverIntervalTableMasterDomain::FRecoverIntervalTableMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RecoverIntervalTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RecoverIntervalTableName(RecoverIntervalTableName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RecoverIntervalTableMaster"
        ))
    {
    }

    FRecoverIntervalTableMasterDomain::FRecoverIntervalTableMasterDomain(
        const FRecoverIntervalTableMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RecoverIntervalTableName(From.RecoverIntervalTableName),
        ParentKey(From.ParentKey)
    {

    }

    FRecoverIntervalTableMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        const Request::FGetRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverIntervalTableMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverIntervalTableName(Self->RecoverIntervalTableName);
        const auto Future = Self->Client->GetRecoverIntervalTableMaster(
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
                    "RecoverIntervalTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FGetTask>> FRecoverIntervalTableMasterDomain::Get(
        Request::FGetRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRecoverIntervalTableMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverIntervalTableMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverIntervalTableName(Self->RecoverIntervalTableName);
        const auto Future = Self->Client->UpdateRecoverIntervalTableMaster(
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
                    "RecoverIntervalTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
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

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FUpdateTask>> FRecoverIntervalTableMasterDomain::Update(
        Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRecoverIntervalTableMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverIntervalTableMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverIntervalTableName(Self->RecoverIntervalTableName);
        const auto Future = Self->Client->DeleteRecoverIntervalTableMaster(
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
                    "RecoverIntervalTableMaster"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FDeleteTask>> FRecoverIntervalTableMasterDomain::Delete(
        Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRecoverIntervalTableMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RecoverIntervalTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RecoverIntervalTableName.IsSet() ? *RecoverIntervalTableName : "null") + ":" +
            ChildType;
    }

    FString FRecoverIntervalTableMasterDomain::CreateCacheKey(
        TOptional<FString> RecoverIntervalTableName
    )
    {
        return FString("") +
            (RecoverIntervalTableName.IsSet() ? *RecoverIntervalTableName : "null");
    }

    FRecoverIntervalTableMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain> Self
    ): Self(Self)
    {

    }

    FRecoverIntervalTableMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FRecoverIntervalTableMaster>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                Self->RecoverIntervalTableName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetRecoverIntervalTableMasterRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                    Self->RecoverIntervalTableName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "recoverIntervalTableMaster")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FRecoverIntervalTableMaster>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                    Self->RecoverIntervalTableName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FModelTask>> FRecoverIntervalTableMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverIntervalTableMasterDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRecoverIntervalTableMasterDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                RecoverIntervalTableName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>(obj));
            }
        );
    }

    void FRecoverIntervalTableMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain::CreateCacheKey(
                RecoverIntervalTableName
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

