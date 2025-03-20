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

#include "Distributor/Domain/Model/TransactionResultAccessToken.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/Expression.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Distributor/Domain/Model/TransactionResultAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FTransactionResultAccessTokenDomain::FTransactionResultAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        TransactionId(TransactionId),
        ParentKey(Gs2::Distributor::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "TransactionResult"
        ))
    {
    }

    FTransactionResultAccessTokenDomain::FTransactionResultAccessTokenDomain(
        const FTransactionResultAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        TransactionId(From.TransactionId),
        ParentKey(From.ParentKey)
    {

    }

    FTransactionResultAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FTransactionResultAccessTokenDomain>& Self,
        const Request::FGetTransactionResultRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTransactionResultAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTransactionResultAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FTransactionResult>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTransactionId(Self->TransactionId);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTransactionResultAccessTokenDomain::FGetTask>> FTransactionResultAccessTokenDomain::Get(
        Request::FGetTransactionResultRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FTransactionResultAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TransactionId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null") + ":" +
            ChildType;
    }

    FString FTransactionResultAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FTransactionResultAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FTransactionResultAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FTransactionResultAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTransactionResultAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FTransactionResult>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Distributor::Model::FTransactionResult> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Distributor::Model::FTransactionResult>(
            Self->ParentKey,
            Gs2::Distributor::Domain::Model::FTransactionResultDomain::CreateCacheKey(
                Self->TransactionId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Distributor::Request::FGetTransactionResultRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Distributor::Domain::Model::FTransactionResultDomain::CreateCacheKey(
                    Self->TransactionId
                );
                Self->Gs2->Cache->Put(
                    Gs2::Distributor::Model::FTransactionResult::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "transactionResult")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Distributor::Model::FTransactionResult>(
                Self->ParentKey,
                Gs2::Distributor::Domain::Model::FTransactionResultDomain::CreateCacheKey(
                    Self->TransactionId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTransactionResultAccessTokenDomain::FModelTask>> FTransactionResultAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTransactionResultAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTransactionResultAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Distributor::Model::FTransactionResultPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Distributor::Model::FTransactionResult::TypeName,
            ParentKey,
            Gs2::Distributor::Domain::Model::FTransactionResultDomain::CreateCacheKey(
                TransactionId
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Distributor::Model::FTransactionResult>(obj));
            }
        );
    }

    void FTransactionResultAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Distributor::Model::FTransactionResult::TypeName,
            ParentKey,
            Gs2::Distributor::Domain::Model::FTransactionResultDomain::CreateCacheKey(
                TransactionId
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

