
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

#include "Chat/Domain/Iterator/DescribeLatestMessagesIterator.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Model/Cache/Message.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Chat::Domain::Iterator
{

    FDescribeLatestMessagesIterator::FDescribeLatestMessagesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Chat::FGs2ChatRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> RoomName,
        const TOptional<FString> Password,
        const TOptional<int32> Category
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        RoomName(RoomName),
        Password(Password),
        Category(Category),
        AccessToken(AccessToken)
    {
    }

    FDescribeLatestMessagesIterator::FDescribeLatestMessagesIterator(
        const FDescribeLatestMessagesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RoomName(From.RoomName),
        Password(From.Password),
        Category(From.Category),
        AccessToken(From.AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeLatestMessagesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeLatestMessagesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeLatestMessagesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeLatestMessagesIterator::FIterator& FDescribeLatestMessagesIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt && *RangeIteratorOpt) ++*RangeIteratorOpt;

        // TryGetList / SetListCached は使わない。Message のリストキャッシュは DescribeMessagesIterator と
        // 同じ親キーで「古い順に StartAt まで揃っている」ことを前提にしており、新しい順のページや
        // カテゴリで絞ったページを載せるとそちらの列挙が欠ける。
        // 空のページでも NextPageToken が続くことがある（サーバーが期限切れのメッセージを除いてから返す）ので、
        // 空のページで列挙を打ち切らずに次のページを読む。
        while (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            // Keep the previous page alive until its iterator has been replaced.
            const auto PreviousRange = Range;
            const auto Request =
                MakeShared<Gs2::Chat::Request::FDescribeLatestMessagesRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithRoomName(Self->RoomName)
                    ->WithPassword(Self->Password)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithCategory(Self->Category)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeLatestMessages(Request);
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
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Chat::Model::FMessagePtr>>();
            const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
            const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Chat::Model::Cache::FMessageCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), CacheOwnerSnapshotUserId, Request->GetRoomName(), Item->GetName(),
                        CacheOwnerSnapshotTimeOffset, Item
                    );
                }
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeLatestMessagesIterator::FIterator FDescribeLatestMessagesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeLatestMessagesIterator::FIterator FDescribeLatestMessagesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeLatestMessagesIterator::FIterator FDescribeLatestMessagesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
