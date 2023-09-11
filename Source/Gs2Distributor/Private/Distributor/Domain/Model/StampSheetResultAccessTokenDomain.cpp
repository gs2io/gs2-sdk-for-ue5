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

#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FStampSheetResultAccessTokenDomain::FStampSheetResultAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        TransactionId(TransactionId),
        ParentKey(Gs2::Distributor::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "StampSheetResult"
        ))
    {
    }

    FStampSheetResultAccessTokenDomain::FStampSheetResultAccessTokenDomain(
        const FStampSheetResultAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        TransactionId(From.TransactionId),
        ParentKey(From.ParentKey)
    {

    }

    FStampSheetResultAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStampSheetResultAccessTokenDomain> Self,
        const Request::FGetStampSheetResultRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStampSheetResultAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithTransactionId(Self->TransactionId);
        const auto Future = Self->Client->GetStampSheetResult(
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
                const auto ParentKey = Gs2::Distributor::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId(),
                    "StampSheetResult"
                );
                const auto Key = Gs2::Distributor::Domain::Model::FStampSheetResultDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTransactionId()
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FStampSheetResult::TypeName,
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

    TSharedPtr<FAsyncTask<FStampSheetResultAccessTokenDomain::FGetTask>> FStampSheetResultAccessTokenDomain::Get(
        Request::FGetStampSheetResultRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FStampSheetResultAccessTokenDomain::CreateCacheParentKey(
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

    FString FStampSheetResultAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FStampSheetResultAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStampSheetResultAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStampSheetResultAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Distributor::Model::FStampSheetResult> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Distributor::Model::FStampSheetResult>(
            Self->ParentKey,
            Gs2::Distributor::Domain::Model::FStampSheetResultDomain::CreateCacheKey(
                Self->TransactionId
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Distributor::Request::FGetStampSheetResultRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Distributor::Domain::Model::FStampSheetResultDomain::CreateCacheKey(
                    Self->TransactionId
                );
                Self->Cache->Put(
                    Gs2::Distributor::Model::FStampSheetResult::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "stampSheetResult")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Distributor::Model::FStampSheetResult>(
                Self->ParentKey,
                Gs2::Distributor::Domain::Model::FStampSheetResultDomain::CreateCacheKey(
                    Self->TransactionId
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStampSheetResultAccessTokenDomain::FModelTask>> FStampSheetResultAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStampSheetResultAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

