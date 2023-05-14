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

// ReSharper disable CppUnusedIncludeDirective

#include "Friend/Domain/Iterator/DescribeFriendsIterator.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/User.h"

namespace Gs2::Friend::Domain::Iterator
{

    FDescribeFriendsIterator::FDescribeFriendsIterator(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Friend::FGs2FriendRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<bool> WithProfile
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        WithProfile(WithProfile)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeFriendsIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendUser>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeFriendsIterator::FIterator::FIterator(
        const TSharedRef<FDescribeFriendsIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeFriendsIterator::FIterator& FDescribeFriendsIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheParentKey(
            Self->NamespaceName,
            Self->UserId(),
            Self->WithProfile.IsSet() ? *Self->WithProfile ? TOptional<FString>("True") : TOptional<FString>("False") : TOptional<FString>("False"),
            "FriendUser"
        );
            if (Self->Cache->IsListCached(
                Gs2::Friend::Model::FFriendUser::TypeName,
                ListParentKey
            )) {
                Range = MakeShared<TArray<Gs2::Friend::Model::FFriendUserPtr>>();
                *Range = Self->Cache->List<Gs2::Friend::Model::FFriendUser>(
                    ListParentKey
                );
                RangeIteratorOpt = Range->CreateIterator();
                PageToken = TOptional<FString>();
                bLast = true;
                bEnd = static_cast<bool>(*RangeIteratorOpt);
                return *this;
            }
            const auto Future = Self->Client->DescribeFriends(
                MakeShared<Gs2::Friend::Request::FDescribeFriendsRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithWithProfile(Self->WithProfile)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
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
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Cache->Put(
                    Gs2::Friend::Model::FFriendUser::TypeName,
                    ListParentKey,
                    Gs2::Friend::Domain::Model::FFriendDomain::CreateCacheKey(
                        Item->GetUserId()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeFriendsIterator::FIterator FDescribeFriendsIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeFriendsIterator::FIterator FDescribeFriendsIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeFriendsIterator::FIterator FDescribeFriendsIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

