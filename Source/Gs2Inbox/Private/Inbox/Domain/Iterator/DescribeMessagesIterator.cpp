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

#include "Inbox/Domain/Iterator/DescribeMessagesIterator.h"
#include "Inbox/Domain/Model/Message.h"
#include "Inbox/Domain/Model/User.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inbox::Domain::Iterator
{

    FDescribeMessagesIterator::FDescribeMessagesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Inbox::FGs2InboxRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<bool> IsRead
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        IsRead(IsRead)
    {
    }

    FDescribeMessagesIterator::FDescribeMessagesIterator(
        const FDescribeMessagesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        IsRead(From.IsRead)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeMessagesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Inbox::Model::FMessage>> Result)
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
        PageToken(TOptional<FString>()),
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
            const auto ListParentKey = Gs2::Inbox::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId(),
                "Message"
            );

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Inbox::Model::FMessage>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Inbox::Model::FMessagePtr& Item) { return Self->IsRead && Item->GetIsRead() != Self->IsRead; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->DescribeMessages(
                MakeShared<Gs2::Inbox::Request::FDescribeMessagesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithAccessToken(Self->AccessToken == nullptr ? TOptional<FString>() : Self->AccessToken->GetToken())
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
                Self->Gs2->Cache->Put(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ListParentKey,
                    Gs2::Inbox::Domain::Model::FMessageDomain::CreateCacheKey(
                        Item->GetName()
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Inbox::Model::FMessagePtr& Item) { return Self->IsRead && Item->GetIsRead() != Self->IsRead; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Inbox::Model::FMessage::TypeName,
                    ListParentKey
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

