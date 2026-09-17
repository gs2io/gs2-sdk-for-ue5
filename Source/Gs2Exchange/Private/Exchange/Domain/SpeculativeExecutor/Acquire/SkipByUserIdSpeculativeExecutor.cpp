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

#include "Exchange/Domain/SpeculativeExecutor/Acquire/SkipByUserIdSpeculativeExecutor.h"
#include "Exchange/Domain/Gs2Exchange.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "Exchange/Model/Cache/Await.h"
#include "Exchange/Model/Cache/RateModel.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Exchange::Domain::SpeculativeExecutor
{

    namespace
    {
        FString SerializeSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FSkipByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Exchange:SkipByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSkipByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FSkipByUserIdRequestPtr& Request,
        Gs2::Exchange::Model::FAwaitPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FSkipByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FSkipByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSkipByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSkipByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto PreparedRequest = MakeShared<Gs2::Exchange::Request::FSkipByUserIdRequest>(*Request);
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId() ||
            !PreparedRequest->GetNamespaceName().IsSet() || !PreparedRequest->GetAwaitName().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto AwaitName = PreparedRequest->GetAwaitName();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        const auto Region = Domain->RestSession->RegionName();
        const auto OwnerId = Domain->RestSession->OwnerId();

        Gs2::Exchange::Model::FAwaitPtr Item;
        const bool AwaitFound = Gs2::Exchange::Model::Cache::FAwaitCache::TryGet(
            Domain->Cache, NamespaceName, UserId, AwaitName, TimeOffset, &Item);
        const FString ExpectedAwaitId = FString::Printf(
            TEXT("grn:gs2:%s:%s:exchange:%s:user:%s:await:%s"),
            *Region, *OwnerId, **NamespaceName, **UserId, **AwaitName);
        if (!AwaitFound || !Item.IsValid() || !Item->GetAwaitId().IsSet() ||
            *Item->GetAwaitId() != ExpectedAwaitId || !Item->GetUserId().IsSet() ||
            *Item->GetUserId() != *UserId || !Item->GetName().IsSet() || *Item->GetName() != *AwaitName ||
            !Item->GetRateName().IsSet() || !Item->GetSkipSeconds().IsSet() || !Item->GetExchangedAt().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto RateName = Item->GetRateName();
        Gs2::Exchange::Model::FRateModelPtr RateModel;
        const bool RateFound = Gs2::Exchange::Model::Cache::FRateModelCache::TryGet(
            Domain->Cache, NamespaceName, RateName, TOptional<int32>(), &RateModel);
        const FString ExpectedRateId = FString::Printf(
            TEXT("grn:gs2:%s:%s:exchange:%s:model:%s"),
            *Region, *OwnerId, **NamespaceName, **RateName);
        if (!RateFound || !RateModel.IsValid() || !RateModel->GetRateModelId().IsSet() ||
            *RateModel->GetRateModelId() != ExpectedRateId || !RateModel->GetName().IsSet() ||
            *RateModel->GetName() != *RateName || !RateModel->GetLockTime().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }

        const int64 TotalLockSeconds = static_cast<int64>(*RateModel->GetLockTime()) * 60;
        const int32 NormalizedLockSeconds = static_cast<int32>(static_cast<int64>(*RateModel->GetLockTime()) * 60);
        const int64 NormalizedAcquirableAt = *Item->GetExchangedAt() +
            (static_cast<int64>(NormalizedLockSeconds) - *Item->GetSkipSeconds()) * 1000;
        int64 SkipSeconds = 0;
        if (PreparedRequest->GetSkipType().IsSet() && *PreparedRequest->GetSkipType() == TEXT("complete"))
        {
            SkipSeconds = TotalLockSeconds;
        }
        else if (PreparedRequest->GetSkipType().IsSet() && *PreparedRequest->GetSkipType() == TEXT("minutes") &&
                 PreparedRequest->GetMinutes().IsSet())
        {
            SkipSeconds = *Item->GetSkipSeconds() + static_cast<int64>(*PreparedRequest->GetMinutes()) * 60;
        }
        else if (PreparedRequest->GetSkipType().IsSet() && *PreparedRequest->GetSkipType() == TEXT("totalRate") &&
                 PreparedRequest->GetRate().IsSet())
        {
            SkipSeconds = *Item->GetSkipSeconds() + static_cast<int64>(static_cast<float>(TotalLockSeconds) * *PreparedRequest->GetRate());
        }
        else if (PreparedRequest->GetSkipType().IsSet() && *PreparedRequest->GetSkipType() == TEXT("remainRate") &&
                 PreparedRequest->GetRate().IsSet())
        {
            const int64 RemainMillis = static_cast<int64>(static_cast<float>(NormalizedAcquirableAt - *Item->GetExchangedAt()) * *PreparedRequest->GetRate());
            SkipSeconds = *Item->GetSkipSeconds() + static_cast<int32>(RemainMillis / 1000);
        }
        else
        {
            *Result = nullptr;
            return nullptr;
        }
        if (SkipSeconds > TotalLockSeconds) SkipSeconds = TotalLockSeconds;
        if (SkipSeconds < 0) SkipSeconds = 0;
        if (SkipSeconds > MAX_int32) SkipSeconds = MAX_int32;
        const auto Changed = MakeShared<Gs2::Exchange::Model::FAwait>(*Item)
            ->WithSkipSeconds(static_cast<int32>(SkipSeconds))
            ->WithAcquirableAt(*Item->GetExchangedAt() - SkipSeconds * 1000 +
                               static_cast<int64>(NormalizedLockSeconds) * 1000)
            ->WithRevision(0);
        const FString AwaitSnapshot = SerializeSnapshot(Item->ToJson());
        const FString RateSnapshot = SerializeSnapshot(RateModel->ToJson());

        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
            MakeShared<TFunction<void()>>([Domain = Domain, PreparedRequest, UserId, TimeOffset,
                                           RateName, Changed, AwaitSnapshot, RateSnapshot]()
        {
            Gs2::Exchange::Model::FAwaitPtr LiveAwait;
            Gs2::Exchange::Model::FRateModelPtr LiveRate;
            const bool AwaitFound = Gs2::Exchange::Model::Cache::FAwaitCache::TryGet(
                Domain->Cache, PreparedRequest->GetNamespaceName(), UserId,
                PreparedRequest->GetAwaitName(), TimeOffset, &LiveAwait);
            const bool RateFound = Gs2::Exchange::Model::Cache::FRateModelCache::TryGet(
                Domain->Cache, PreparedRequest->GetNamespaceName(), RateName,
                TOptional<int32>(), &LiveRate);
            if (!AwaitFound || !LiveAwait.IsValid() || SerializeSnapshot(LiveAwait->ToJson()) != AwaitSnapshot ||
                !RateFound || !LiveRate.IsValid() || SerializeSnapshot(LiveRate->ToJson()) != RateSnapshot)
            {
                return;
            }
            Domain->Cache->Put(
                Gs2::Exchange::Model::FAwait::TypeName,
                Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheParentKey(
                    PreparedRequest->GetNamespaceName(), UserId, TimeOffset),
                Gs2::Exchange::Model::Cache::FAwaitCache::CreateCacheKey(
                    PreparedRequest->GetAwaitName()),
                Changed,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes));
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSkipByUserIdSpeculativeExecutor::FCommitTask>> FSkipByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FSkipByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Exchange::Request::FSkipByUserIdRequestPtr FSkipByUserIdSpeculativeExecutor::Rate(
        const Gs2::Exchange::Request::FSkipByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetMinutes().IsSet())
        {
            Request->WithMinutes(*Request->GetMinutes() * Rate);
        }
        return Request;
    }

    Gs2::Exchange::Request::FSkipByUserIdRequestPtr FSkipByUserIdSpeculativeExecutor::Rate(
        const Gs2::Exchange::Request::FSkipByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetMinutes().IsSet())
        {
            Rate.Multiply(*Request->GetMinutes());
            Request->WithMinutes(Rate.ToInt());
        }
        return Request;
    }
}
