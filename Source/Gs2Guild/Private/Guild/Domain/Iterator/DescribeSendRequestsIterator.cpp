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

// ReSharper disable CppUnusedIncludeDirective

#include "Guild/Domain/Iterator/DescribeSendRequestsIterator.h"

#include "Core/Domain/Gs2.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Model/Cache/SendMemberRequest.h"


namespace Gs2::Guild::Domain::Iterator
{

    FDescribeSendRequestsIterator::FDescribeSendRequestsIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Guild::FGs2GuildRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> GuildModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        GuildModelName(GuildModelName)
    {
    }

    FDescribeSendRequestsIterator::FDescribeSendRequestsIterator(
        const FDescribeSendRequestsIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        GuildModelName(From.GuildModelName)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeSendRequestsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Guild::Model::FSendMemberRequest>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeSendRequestsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeSendRequestsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeSendRequestsIterator::FIterator& FDescribeSendRequestsIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt && *RangeIteratorOpt) ++*RangeIteratorOpt;


        // Keep the previous page alive until its iterator has been replaced.

        const auto PreviousRange = Range;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(

                Self->NamespaceName,
                Self->GuildModelName,

                Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),

                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()

            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Guild::Model::FSendMemberRequest>(ListParentKey);

                if (Range)
                {
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Request =

                MakeShared<Gs2::Guild::Request::FDescribeSendRequestsRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithGuildModelName(Self->GuildModelName)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize);

            const auto Future = Self->Client->DescribeSendRequests(Request);

            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Guild::Model::FSendMemberRequestPtr>>();

            const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();

            const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();

            if (R.IsValid() && R->GetItems().IsValid())

            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {

                    if (!Item.IsValid()) continue;

                    Gs2::Guild::Model::Cache::FSendMemberRequestCache::Put(

                        Self->Gs2->Cache,

                        Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Self->GuildModelName, Item->GetTargetGuildName(),

                        CacheOwnerSnapshotTimeOffset, Item

                    );

                }

            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Guild::Model::FSendMemberRequest::TypeName,
                    Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(

                        Self->NamespaceName,

                        Self->GuildModelName,

                        Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),

                        Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()

                    )

                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeSendRequestsIterator::FIterator FDescribeSendRequestsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeSendRequestsIterator::FIterator FDescribeSendRequestsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeSendRequestsIterator::FIterator FDescribeSendRequestsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
