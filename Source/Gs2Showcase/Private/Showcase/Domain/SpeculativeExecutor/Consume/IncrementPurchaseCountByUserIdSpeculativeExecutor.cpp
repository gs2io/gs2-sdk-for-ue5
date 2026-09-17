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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Showcase/Domain/SpeculativeExecutor/Consume/IncrementPurchaseCountByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Showcase/Domain/Gs2Showcase.h"
#include "Showcase/Domain/SpeculativeExecutor/PurchaseCountSpeculativeCommit.h"
#include "Showcase/Model/Cache/RandomDisplayItem.h"

#include <cmath>
#include <cstdint>

namespace Gs2::Showcase::Domain::SpeculativeExecutor
{
    using Private::FPurchaseCountSpeculativeCommit;

    FString FIncrementPurchaseCountByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Showcase:IncrementPurchaseCountByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request,
        Gs2::Showcase::Model::FRandomDisplayItemPtr& Item
    )
    {
        static_cast<void>(Domain);
        static_cast<void>(AccessToken);
        if (!Request.IsValid())
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                return Arr;
            }());
        }
        int32 Count = 1;
        Count = Request->GetCount().Get(1);
        const auto Changed = FPurchaseCountSpeculativeCommit::Transform(
            Item, Count
        );
        if (!Changed.IsValid()) {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                return Arr;
            }());
        }
        Item = Changed;
        return nullptr;
    }

    FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr PreparedRequest;
        if (Request.IsValid())
        {
            PreparedRequest = Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequest::FromJson(
                Request->ToJson()
            );
        }
        if (PreparedRequest.IsValid() && PreparedRequest->GetUserId().IsSet() &&
            *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            TOptional<FString> UserId;
            if (AccessToken.IsValid())
            {
                UserId = AccessToken->GetUserId();
            }
            PreparedRequest->WithUserId(UserId);
        }
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid())
        {
            PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        }
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedAccessToken.IsValid() || !PreparedAccessToken->GetUserId().IsSet() ||
            PreparedAccessToken->GetUserId().Get(FString()).IsEmpty() ||
            PreparedRequest->GetUserId() != PreparedAccessToken->GetUserId())
        {
            return nullptr;
        }

        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        Gs2::Showcase::Model::FRandomDisplayItemPtr PreparedItem;
        if (!Gs2::Showcase::Model::Cache::FRandomDisplayItemCache::TryGet(
            Domain->Cache, PreparedRequest->GetNamespaceName(), UserId,
            PreparedRequest->GetShowcaseName(), PreparedRequest->GetDisplayItemName(),
            TimeOffset, &PreparedItem
        ) || !PreparedItem.IsValid() ||
            PreparedItem->GetShowcaseName() != PreparedRequest->GetShowcaseName() ||
            PreparedItem->GetName() != PreparedRequest->GetDisplayItemName())
        {
            return nullptr;
        }

        const int32 Count = PreparedRequest->GetCount().Get(1);
        auto PreparedValidation = PreparedItem;
        const auto Err = Transform(Domain, PreparedAccessToken, PreparedRequest, PreparedValidation);
        if (Err != nullptr)
        {
            return Err;
        }
        *Result = FPurchaseCountSpeculativeCommit::Create(
            Domain->Cache, PreparedRequest->GetNamespaceName(), UserId,
            PreparedRequest->GetShowcaseName(), PreparedRequest->GetDisplayItemName(),
            TimeOffset, PreparedItem, Count
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIncrementPurchaseCountByUserIdSpeculativeExecutor::FCommitTask>> FIncrementPurchaseCountByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid() || std::isnan(Rate) || std::isinf(Rate))
        {
            return nullptr;
        }
        const int32 Count = Request->GetCount().Get(1);
        if (Count == 0)
        {
            Request->WithCount(0);
            return Request;
        }
        uint64 Bits = 0;
        FMemory::Memcpy(&Bits, &Rate, sizeof(Bits));
        const int32 ExponentBits = static_cast<int32>((Bits >> 52) & 0x7ffULL);
        const uint64 Fraction = Bits & 0x000fffffffffffffULL;
        uint64 Significand = ExponentBits == 0
            ? Fraction
            : (Fraction | 0x0010000000000000ULL);
        const bool Negative = ((Bits & 0x8000000000000000ULL) != 0) != (Count < 0);
        const int32 Exponent = ExponentBits == 0 ? -1074 : ExponentBits - 1075;
        using FUnsignedBigInt = TBigInt<1024, false>;
        FUnsignedBigInt Product(static_cast<int64>(Count < 0 ? -static_cast<int64>(Count) : Count));
        Product *= FUnsignedBigInt(static_cast<int64>(Significand));
        if (Exponent >= 0)
        {
            if (Exponent > 31)
            {
                return nullptr;
            }
            Product <<= Exponent;
        }
        else
        {
            const int32 Shift = -Exponent;
            Product >>= Shift;
        }
        const int64 MaximumMagnitude = Negative ? 2147483648LL : 2147483647LL;
        if (Product > FUnsignedBigInt(MaximumMagnitude))
        {
            return nullptr;
        }
        const int64 Magnitude = Product.ToInt();
        const int32 Value = static_cast<int32>(Negative ? -Magnitude : Magnitude);
        Request->WithCount(Value);
        return Request;
    }

    Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr FIncrementPurchaseCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Showcase::Request::FIncrementPurchaseCountByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid())
        {
            return nullptr;
        }
        const int32 Count = Request->GetCount().Get(1);
        const bool Negative = Count < 0;
        using FUnsignedBigInt = TBigInt<1024, false>;
        FUnsignedBigInt Product(static_cast<int64>(Negative ? -static_cast<int64>(Count) : Count));
        Product *= Rate;
        const int64 MaximumMagnitude = Negative ? 2147483648LL : 2147483647LL;
        if (Product > FUnsignedBigInt(MaximumMagnitude))
        {
            return nullptr;
        }
        const int64 Magnitude = Product.ToInt();
        Request->WithCount(static_cast<int32>(Negative ? -Magnitude : Magnitude));
        return Request;
    }
}
