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
#include "Chat/Domain/Iterator/DescribeMessagesStartAt.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/Room.h"

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
        StartAt(TOptional<int64>()),
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

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Chat::Domain::Model::FRoomDomain::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<FString>("Singleton"),
                Self->RoomName,
                "Message"
            );

            if (!RangeIteratorOpt)
            {
                TSharedPtr<FGs2Object> UpdateContext;
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

            const auto Future = Self->Client->DescribeLatestMessages(
                MakeShared<Gs2::Chat::Request::FDescribeLatestMessagesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithRoomName(Self->RoomName)
                    ->WithPassword(Self->Password)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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
                Self->Gs2->Cache->Put(
                    Gs2::Chat::Model::FMessage::TypeName,
                    ListParentKey,
                    Gs2::Chat::Domain::Model::FMessageDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
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

