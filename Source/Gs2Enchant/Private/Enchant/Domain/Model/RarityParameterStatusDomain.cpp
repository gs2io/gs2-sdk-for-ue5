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

#include "Enchant/Domain/Model/RarityParameterStatus.h"
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
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FRarityParameterStatusDomain::FRarityParameterStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> ParameterName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParameterName(ParameterName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "RarityParameterStatus"
        ))
    {
    }

    FRarityParameterStatusDomain::FRarityParameterStatusDomain(
        const FRarityParameterStatusDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParameterName(From.ParameterName),
        PropertyId(From.PropertyId),
        ParentKey(From.ParentKey)
    {

    }

    FRarityParameterStatusDomain::FGetTask::FGetTask(
        const TSharedPtr<FRarityParameterStatusDomain>& Self,
        const Request::FGetRarityParameterStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithParameterName(Self->ParameterName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetRarityParameterStatusByUserId(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "RarityParameterStatus"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetParameterName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FGetTask>> FRarityParameterStatusDomain::Get(
        Request::FGetRarityParameterStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRarityParameterStatusDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRarityParameterStatusDomain>& Self,
        const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithParameterName(Self->ParameterName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->DeleteRarityParameterStatusByUserId(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "RarityParameterStatus"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetParameterName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Delete(Gs2::Enchant::Model::FRarityParameterStatus::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FDeleteTask>> FRarityParameterStatusDomain::Delete(
        Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FRarityParameterStatusDomain::FReDrawTask::FReDrawTask(
        const TSharedPtr<FRarityParameterStatusDomain>& Self,
        const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusDomain::FReDrawTask::FReDrawTask(
        const FReDrawTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FReDrawTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithParameterName(Self->ParameterName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->ReDrawRarityParameterStatusByUserId(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "RarityParameterStatus"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetParameterName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FReDrawTask>> FRarityParameterStatusDomain::ReDraw(
        Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FReDrawTask>>(this->AsShared(), Request);
    }

    FRarityParameterStatusDomain::FAddTask::FAddTask(
        const TSharedPtr<FRarityParameterStatusDomain>& Self,
        const Request::FAddRarityParameterStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusDomain::FAddTask::FAddTask(
        const FAddTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FAddTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithParameterName(Self->ParameterName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->AddRarityParameterStatusByUserId(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "RarityParameterStatus"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetParameterName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FAddTask>> FRarityParameterStatusDomain::Add(
        Request::FAddRarityParameterStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddTask>>(this->AsShared(), Request);
    }

    FRarityParameterStatusDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FRarityParameterStatusDomain>& Self,
        const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName)
            ->WithUserId(Self->UserId)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->VerifyRarityParameterStatusByUserId(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "RarityParameterStatus"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetParameterName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FVerifyTask>> FRarityParameterStatusDomain::Verify(
        Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FRarityParameterStatusDomain::FSetTask::FSetTask(
        const TSharedPtr<FRarityParameterStatusDomain>& Self,
        const Request::FSetRarityParameterStatusByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusDomain::FSetTask::FSetTask(
        const FSetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FSetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithParameterName(Self->ParameterName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->SetRarityParameterStatusByUserId(
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
                const auto ParentKey = Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "RarityParameterStatus"
                );
                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetParameterName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
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

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FSetTask>> FRarityParameterStatusDomain::Set(
        Request::FSetRarityParameterStatusByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetTask>>(this->AsShared(), Request);
    }

    FString FRarityParameterStatusDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> ParameterName,
        TOptional<FString> PropertyId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (ParameterName.IsSet() ? *ParameterName : "null") + ":" +
            (PropertyId.IsSet() ? *PropertyId : "null") + ":" +
            ChildType;
    }

    FString FRarityParameterStatusDomain::CreateCacheKey(
        TOptional<FString> ParameterName,
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (ParameterName.IsSet() ? *ParameterName : "null") + ":" + 
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FRarityParameterStatusDomain::FModelTask::FModelTask(
        const TSharedPtr<FRarityParameterStatusDomain> Self
    ): Self(Self)
    {

    }

    FRarityParameterStatusDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Enchant::Model::FRarityParameterStatus>(
            Self->ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                Self->ParameterName,
                Self->PropertyId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Enchant::Request::FGetRarityParameterStatusByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    Self->ParameterName,
                    Self->PropertyId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "rarityParameterStatus")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Enchant::Model::FRarityParameterStatus>(
                Self->ParentKey,
                Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                    Self->ParameterName,
                    Self->PropertyId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterStatusDomain::FModelTask>> FRarityParameterStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRarityParameterStatusDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRarityParameterStatusDomain::Subscribe(
        TFunction<void(Gs2::Enchant::Model::FRarityParameterStatusPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                ParameterName,
                PropertyId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>(obj));
            }
        );
    }

    void FRarityParameterStatusDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Enchant::Model::FRarityParameterStatus::TypeName,
            ParentKey,
            Gs2::Enchant::Domain::Model::FRarityParameterStatusDomain::CreateCacheKey(
                ParameterName,
                PropertyId
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

