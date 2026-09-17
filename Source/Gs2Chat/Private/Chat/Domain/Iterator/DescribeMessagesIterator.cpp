
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

#include "Chat/Domain/Iterator/DescribeMessagesIterator.h"
#include "Chat/Domain/Iterator/DescribeMessagesStartAt.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Model/Cache/Message.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Chat::Domain::Iterator
{

    FDescribeMessagesIterator::FDescribeMessagesIterator(
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

    FDescribeMessagesIterator::FDescribeMessagesIterator(
        const FDescribeMessagesIterator& From
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

    Gs2::Core::Model::FGs2ErrorPtr FDescribeMessagesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeMessagesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeMessagesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        StartAt(TOptional<int64>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeMessagesIterator::FIterator& FDescribeMessagesIterator::FIterator::operator++()
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
            const auto ListParentKey = Gs2::Chat::Model::Cache::FMessageCache::CreateCacheParentKey(
                Self->NamespaceName,
                Self->AccessToken.IsValid() ? Self->AccessToken->GetUserId() : TOptional<FString>(),
                Self->RoomName,
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
            );
                TSharedPtr<FGs2Object> UpdateContext;
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Chat::Model::FMessage>(ListParentKey, &UpdateContext);

                if (Range)
                {
                    if (UpdateContext)
                    {
                        auto UpdateContextValue = StaticCastSharedPtr<FDescribeMessagesStartAt>(UpdateContext)->Value;
                        Range->RemoveAll([UpdateContextValue](const Gs2::Chat::Model::FMessagePtr& Message){ return *Message->GetCreatedAt() >= UpdateContextValue; });
                        StartAt = UpdateContextValue;
                        bLast = false;
                    }
                    else
                    {
                        bLast = true;
                    }
                    RangeIteratorOpt = Range->CreateIterator();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Request =
                MakeShared<Gs2::Chat::Request::FDescribeMessagesRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithRoomName(Self->RoomName)
                    ->WithPassword(Self->Password)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
                    ->WithStartAt(StartAt)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeMessages(Request);
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
            if (Range)
            {
                if (UpdateContext)
                {
                    auto UpdateContextValue = StaticCastSharedPtr<FDescribeMessagesStartAt>(UpdateContext)->Value;
                    Range->RemoveAll([UpdateContextValue](const Gs2::Chat::Model::FMessagePtr& Message){ return *Message->GetCreatedAt() >= UpdateContextValue; });
                    StartAt = UpdateContextValue;
                    bLast = false;
                }
                else
                {
                    bLast = true;
                }
            }
            RangeIteratorOpt = Range->CreateIterator();
            if (Range->Num() > 0) {
                StartAt = *(*Range)[Range->Num()-1]->GetCreatedAt() + 1;
            } else {
                bLast = true;
            }
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Chat::Model::FMessage::TypeName,
                    ListParentKey,
                    StartAt
                        // ReSharper disable once CppSmartPointerVsMakeFunction
                        ? TSharedPtr<FGs2Object>(new FDescribeMessagesStartAt(*StartAt))
                        : nullptr
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeMessagesIterator::FIterator FDescribeMessagesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeMessagesIterator::FIterator FDescribeMessagesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeMessagesIterator::FIterator FDescribeMessagesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

