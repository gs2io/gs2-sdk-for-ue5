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

#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FRarityParameterStatusAccessTokenDomain::FRarityParameterStatusAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> ParameterName,
        const TOptional<FString> PropertyId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParameterName(ParameterName),
        PropertyId(PropertyId),
        ParentKey(Gs2::Enchant::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "RarityParameterStatus"
        ))
    {
    }

    FRarityParameterStatusAccessTokenDomain::FRarityParameterStatusAccessTokenDomain(
        const FRarityParameterStatusAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParameterName(From.ParameterName),
        PropertyId(From.PropertyId),
        ParentKey(From.ParentKey)
    {

    }

    FRarityParameterStatusAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FRarityParameterStatusAccessTokenDomain>& Self,
        const Request::FGetRarityParameterStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterStatus>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithParameterName(Self->ParameterName)
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->GetRarityParameterStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterStatusAccessTokenDomain::FGetTask>> FRarityParameterStatusAccessTokenDomain::Get(
        Request::FGetRarityParameterStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRarityParameterStatusAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FRarityParameterStatusAccessTokenDomain>& Self,
        const Request::FVerifyRarityParameterStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterStatusAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Domain::Model::FRarityParameterStatusAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithPropertyId(Self->PropertyId);
        const auto Future = Self->Client->VerifyRarityParameterStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterStatusAccessTokenDomain::FVerifyTask>> FRarityParameterStatusAccessTokenDomain::Verify(
        Request::FVerifyRarityParameterStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FRarityParameterStatusAccessTokenDomain::CreateCacheParentKey(
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

    FString FRarityParameterStatusAccessTokenDomain::CreateCacheKey(
        TOptional<FString> ParameterName,
        TOptional<FString> PropertyId
    )
    {
        return FString("") +
            (ParameterName.IsSet() ? *ParameterName : "null") + ":" + 
            (PropertyId.IsSet() ? *PropertyId : "null");
    }

    FRarityParameterStatusAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FRarityParameterStatusAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FRarityParameterStatusAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterStatusAccessTokenDomain::FModelTask::Action(
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
                MakeShared<Gs2::Enchant::Request::FGetRarityParameterStatusRequest>()
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

    TSharedPtr<FAsyncTask<FRarityParameterStatusAccessTokenDomain::FModelTask>> FRarityParameterStatusAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRarityParameterStatusAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FRarityParameterStatusAccessTokenDomain::Subscribe(
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

    void FRarityParameterStatusAccessTokenDomain::Unsubscribe(
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

